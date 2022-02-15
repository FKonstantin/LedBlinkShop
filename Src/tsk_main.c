/*
* led_run_blink.h - LED_MODE_1 - SemLedMode1
* led_on_all.h - LED_MODE_2 - SemLedMode2
* led_all_blink.h - LED_MODE_3 - SemLedMode3
* led_1_4_8_12_16_blinl.h - LED_MODE_4 - SemLedMode4
* led_runing_1.h - LED_MODE_5 - SemLedMode5
* led_demo.h - LED_MODE_6 - SemLedMode6
*/


#include "tsk_main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "semaphores.h"
#include "lcd_lib.h"
#include "tim.h"
#include "tsk_encoder.h"
#include "led_run_blink.h"
#include "flash_read_write.h"

#define LED_BLINK_SPEED_0						5
#define LED_BLINK_SPEED_1						10
#define LED_BLINK_SPEED_2						15
#define LED_BLINK_SPEED_3						20
#define LED_BLINK_SPEED_4						25
#define LED_BLINK_SPEED_5						30
#define LED_BLINK_SPEED_6						35
#define LED_BLINK_SPEED_7						40
#define LED_BLINK_SPEED_8						45
#define LED_BLINK_SPEED_9						50
#define LED_BLINK_SPEED_10						55
#define LED_BLINK_SPEED_11						60
#define LED_BLINK_SPEED_12						65
#define LED_BLINK_SPEED_13						70
#define LED_BLINK_SPEED_14						75
#define LED_BLINK_SPEED_15						80
#define LED_BLINK_SPEED_16						85
#define LED_BLINK_SPEED_17						90
#define LED_BLINK_SPEED_18						95
#define LED_STEP_SPEED							5

#define LED_MODE_1								1
#define LED_MODE_2								2
#define LED_MODE_3								3
#define LED_MODE_4								4
#define LED_MODE_5								5
#define LED_MODE_6								6


extern unsigned char ADDR_LCD;                  								// переменная для хранения адреса ЖКИ (объявленна в lcd_lib.h) необходима для вызова LCD_ON и т.д.
extern unsigned char DISPLAY_CONTROL;           								// указываем переменную для запоминания состояния ЖКИ и курсора
extern unsigned char port_C;                                                   	// указываем переменную эквивалент регистра порта
extern unsigned char Acol; 														// Переменная для хранения позиции курсора колонка 
uint32_t cntBtnUp = 0;
// Speed blink led in ms/10
uint32_t currentSpeedMs = 0;
uint32_t currentLedMode = 0;
uint32_t encodStartValue = 0;
uint32_t encodCnt = 0;
uint32_t encodCntOld = 0;


static void setLedPower(uint32_t value);
static int convertRange(int numValue, int fromLow, int fromHigh, int toLow, int toHigh);
static void btnUpMain(void);
static void btnDownMain(void);
static void btnLeftMain(void);
static void btnRightMain(void);
static void btnEncodMain(void);
static void setLedMode(void);
static void lcdWriteMode(void);
static void readSettings(void);
static void writeSettings(void);
static void lcdShowEncodCnt(void);

//-----------------------------------------------------------------------------
void tsk_main(void)
{
	lcd_init(ADDR_DEV_LCD);	
	LCD_ON;
	LCD_CURSOR_OFF;
	lcdClear();
	semInit();
	// Start PWM
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);			
	
	lcdSendString(0, 1, "Ярк:");
	lcdSendString(0, 9, "Скор:");	
	
	// Load settings 
	readSettings();
	encodSetValue(encodStartValue);
	setLedMode();
	lcdWriteMode();	
	
	while(1)
	{
		btnUpMain();
		btnDownMain();
		btnLeftMain();
		btnRightMain();
		btnEncodMain();		
		setLedPower(encodGetValue());
		lcdShowEncodCnt();			
		osDelay(10);		
	}
}

//-----------------------------------------------------------------------------
static void setLedPower(uint32_t value)
{
	uint32_t numPwm = 0;
	
	
	numPwm = convertRange(value, 0, 100, 0, 65500);
	TIM4->CCR3 = numPwm;;		
}

//------------------------------------------------------------------------------
/**
  * @brief  The function converts a number from one number range to another
  * @param  @arg numValue - The number that you want to convert
  * @param  @arg fromLow - The minimum number of the range from which to convert the number
  * @param  @arg fromHigh - The maximum number of the range from which to convert the number
  * @param  @arg toLow - The minimum number of the range to convert the number to
  * @param  @arg toHigh - The maximum number of the range to convert the number to
  * @retval None
  */
static int convertRange(int numValue, int fromLow, int fromHigh, int toLow, int toHigh)
{
	return (numValue - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

//-----------------------------------------------------------------------------
static void btnUpMain(void)
{
	if(getSemaphor(SemBtnUpHandle))
	{		
		// In mode 2 disable speed set
		if(getSemaphor(SemLedMode2Handle))
			return;
		
		if(currentSpeedMs <= LED_BLINK_SPEED_17)
		{
			currentSpeedMs += LED_STEP_SPEED;
			lcdSendNumInt(0, 14, currentSpeedMs);				
			osDelay(100);
		}			
	}
}
	
//------------------------------------------------------------------------------
static void btnDownMain(void)
{
	if(getSemaphor(SemBtnDownHandle))
	{
		// In mode 2 disable speed set
		if(getSemaphor(SemLedMode2Handle))
			return;
		
		if(currentSpeedMs >= LED_BLINK_SPEED_1)
		{
			currentSpeedMs -= LED_STEP_SPEED;
			lcdClrChar(0, 15);
			lcdSendNumInt(0, 14, currentSpeedMs);							
			osDelay(100);
		}			
	}
}

//-----------------------------------------------------------------------------
static void btnLeftMain(void)
{
	if(getSemaphor(SemBtnLeftHandle))
	{
		if(currentLedMode >= LED_MODE_2)
		{
			currentLedMode--;
			setLedMode();
			lcdWriteMode();
			osDelay(100);
		}
	}
}

//-----------------------------------------------------------------------------
static void btnRightMain(void)
{
	if(getSemaphor(SemBtnRightHandle))
	{		
		if(currentLedMode < LED_MODE_6) 
		{
			currentLedMode++;
			setLedMode();
			lcdWriteMode();
			osDelay(100);
		}
	}
}

//-----------------------------------------------------------------------------
static void btnEncodMain(void)
{
	if(getSemaphor(SemBtnEncodHandle))
	{
		encodStartValue = encodGetValue();
		writeSettings();
		lcdClear();
		lcdSendString(0, 1, "Настройки");
		lcdSendString(1, 1, "Сохранены");
		osDelay(2000);
		lcdClear();
		lcdWriteMode();
		lcdClrChar(0, 7);
		lcdSendNumInt(0, 5, encodCnt);	
	}
}

//-----------------------------------------------------------------------------
static void setLedMode(void)
{
	switch (currentLedMode)
	{
		case LED_MODE_1:
			setSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		case LED_MODE_2:
			setSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		case LED_MODE_3:
			setSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		case LED_MODE_4:
			setSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		case LED_MODE_5:
			setSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		case LED_MODE_6:
			setSemaphor(SemLedMode6Handle);
			clrSemaphor(SemLedMode1Handle);
			clrSemaphor(SemLedMode2Handle);
			clrSemaphor(SemLedMode3Handle);
			clrSemaphor(SemLedMode4Handle);
			clrSemaphor(SemLedMode5Handle);
			clrSemaphor(SemLedMode7Handle);
			clrSemaphor(SemLedMode8Handle);
			clrSemaphor(SemLedMode9Handle);
			clrSemaphor(SemLedMode10Handle);
			break;
		default:
			break;
	}					
}

//-----------------------------------------------------------------------------
uint32_t getLedSpeed(void)
{
	return currentSpeedMs;
}

//-----------------------------------------------------------------------------
static void lcdWriteMode(void)
{
	switch (currentLedMode)
	{
		case LED_MODE_1:			
			lcdClrChars(0, 14, 15);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(0, 9, "Скор:");	
			lcdSendNumInt(0, 14, currentSpeedMs);
			lcdClrChars(1, 0, 16);
			lcdSendString(1, 0, "Бегущая 1 и 0");
			break;
		case LED_MODE_2:
			lcdClrChars(0, 9, 15);			
			lcdClrChars(1, 0, 16);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(1, 0, "Все горят пост.");
			break;
		case LED_MODE_3:			
			lcdClrChars(0, 14, 15);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(0, 9, "Скор:");	
			lcdSendNumInt(0, 14, currentSpeedMs);
			lcdClrChars(1, 0, 16);
			lcdSendString(1, 0, "Все миг. одновр.");
			break;
		case LED_MODE_4:			
			lcdClrChars(0, 14, 15);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(0, 9, "Скор:");	
			lcdSendNumInt(0, 14, currentSpeedMs);
			lcdClrChars(1, 0, 16);
			lcdSendString(1, 0, "Миг.1-4-8-12-16+");
			break;
		case LED_MODE_5:			
			lcdClrChars(0, 14, 15);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(0, 9, "Скор:");	
			lcdSendNumInt(0, 14, currentSpeedMs);
			lcdClrChars(1, 0, 16);
			lcdSendString(1, 0, "Бегущая 1");
			break;
		case LED_MODE_6:			
			lcdClrChars(0, 14, 15);
			lcdSendString(0, 1, "Ярк:");
			lcdSendString(0, 9, "Скор:");	
			lcdSendNumInt(0, 14, currentSpeedMs);
			lcdClrChars(1, 0, 16);
			lcdSendString(1, 0, "Режим ДЕМО");
			break;
		default:
			break;
	}					
}

//-------------------------------------------------------------------------------- 
/**
  * @brief  Reads the settings from the flash.
  * @param  None  
  * @retval None
  */
static void readSettings(void)
{	
	//--- Read parameters from flash
	currentSpeedMs = flashRead(FLASH_PAGE_50_PART_0);
	currentLedMode = flashRead(FLASH_PAGE_51_PART_0);
	encodStartValue = flashRead(FLASH_PAGE_52_PART_0);	
	// Check setting
	if(currentSpeedMs < LED_BLINK_SPEED_0) 
		currentSpeedMs = LED_BLINK_SPEED_4;
	else if(currentSpeedMs > LED_BLINK_SPEED_18)
		currentSpeedMs = LED_BLINK_SPEED_4;
		
	if((currentLedMode != LED_MODE_1) && (currentLedMode != LED_MODE_2) && (currentLedMode != LED_MODE_3) 
		&& (currentLedMode != LED_MODE_4) && (currentLedMode != LED_MODE_5) && (currentLedMode != LED_MODE_6))
		currentLedMode = LED_MODE_6;
	
	if(encodStartValue < 15)
		encodStartValue = 97;
	else if(encodStartValue > 100)
		encodStartValue = 97;
}

//--------------------------------------------------------------------------------
/**
  * @brief  Write settings to flash
  * @param  None  
  * @retval None
  */
static void writeSettings(void)
{
	flashWriteData(FLASH_PAGE_50_PART_0, currentSpeedMs);
	flashWriteData(FLASH_PAGE_51_PART_0, currentLedMode);
	flashWriteData(FLASH_PAGE_52_PART_0, encodStartValue);	
}

//--------------------------------------------------------------------------------
static void lcdShowEncodCnt(void)
{	
	encodCnt = encodGetValue();
	if(encodCnt == encodCntOld)
	{		
		return;
	}
	else
	{
		lcdClrChar(0, 7);
		lcdSendNumInt(0, 5, encodCnt);		
	}
	
	encodCntOld = encodCnt;	
}










