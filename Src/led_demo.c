/*
* led_demo.h - LED_MODE_6 - SemLedMode6
*/


#include "led_demo.h"
#include "stm32f1xx_hal.h"
#include "tsk_main.h"
#include "semaphores.h"
#include <stdbool.h>



static bool delayWithSemaphor(uint32_t timeDivisionOn10);
static void ledOffAll(void);


//-----------------------------------------------------------------------------
void ledDemo(void)
{
	while(1)
	{
		// ledRunBlink();
		for(int i = 0; i < 5; i++)
		{
			// Led ON
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;					
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);	
			if(delayWithSemaphor(getLedSpeed())) return;		
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);
			
			//Led OFF
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);	
			if(delayWithSemaphor(getLedSpeed())) return;		
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);
			if(delayWithSemaphor(getLedSpeed())) return;
		}
		
		ledOffAll();
		
		// ledOnAll();
		HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);
		osDelay(5000);
		ledOffAll();
		
		// ledAllBlink();
		for(int i = 0; i < 5; i++)
		{
			// Led ON
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);			
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_SET);		
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);
			if(delayWithSemaphor(getLedSpeed())) return;

			//Led OFF
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);			
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_RESET);		
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);	
			if(delayWithSemaphor(getLedSpeed())) return;		
		}	

		ledOffAll();		
		
		// led1_4Blink();
		for(int i = 0; i < 5; i++)
		{
			// 1 Round
			// Led 1 ON/OFF 
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 4 ON/OFF 
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 8 ON/OFF 
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 12 ON/OFF 
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 16 ON/OFF 
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;

			// 2 Round
			// Led 2 ON/OFF 
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 5 ON/OFF 
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 9 ON/OFF 
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 13 ON/OFF 
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;

			// 3 Round
			// Led 3 ON/OFF 
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 6 ON/OFF 
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 10 ON/OFF 
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 14 ON/OFF 
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;

			// 4 Round
			// Led 4 ON/OFF 
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 7 ON/OFF 
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 11 ON/OFF 
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 15 ON/OFF 
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;

			// 5 Round
			// Led 5 ON/OFF 
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 8 ON/OFF 
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 12 ON/OFF 
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 16 ON/OFF 
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;

		}
		
		ledOffAll();		
		
		// ledRuning1();
		for(int i = 0; i < 5; i++)
		{		
			// Led 1 ON/OFF 
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 2 ON/OFF 
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 3 ON/OFF 
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 4 ON/OFF 
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 5 ON/OFF 
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 6 ON/OFF 
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 7 ON/OFF 
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 8 ON/OFF 
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 9 ON/OFF 
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 10 ON/OFF 
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 11 ON/OFF 
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 12 ON/OFF 
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 13 ON/OFF 
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 14 ON/OFF 
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 15 ON/OFF 
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			// Led 16 ON/OFF 
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_SET);		
			if(delayWithSemaphor(getLedSpeed())) return;
			HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);		
			if(delayWithSemaphor(getLedSpeed())) return;						
		}
		
		ledOffAll();	
	}	
}

//-----------------------------------------------------------------------------
static bool delayWithSemaphor(uint32_t timeDivisionOn10)
{
	for(int i = 0; i < timeDivisionOn10; i++)
	{
		if(!getSemaphor(SemLedMode6Handle))		
			return true;
		
		osDelay(10);
	}
	
	return false;
}

static void ledOffAll(void)
{
	HAL_GPIO_WritePin(Led1_GPIO_Port, Led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led2_GPIO_Port, Led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led3_GPIO_Port, Led3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led4_GPIO_Port, Led4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led5_GPIO_Port, Led5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led6_GPIO_Port, Led6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led7_GPIO_Port, Led7_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led8_GPIO_Port, Led8_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led9_GPIO_Port, Led9_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led10_GPIO_Port, Led10_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led11_GPIO_Port, Led11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led12_GPIO_Port, Led12_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led13_GPIO_Port, Led13_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led14_GPIO_Port, Led14_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led15_GPIO_Port, Led15_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led16_GPIO_Port, Led16_Pin, GPIO_PIN_RESET);
}








