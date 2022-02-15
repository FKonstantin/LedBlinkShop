#include "tsk_encoder.h"
#include "tim.h"
#include <stdbool.h>
#include "semaphores.h"


#define MAX_PERMIT_VALUE_ENCODER				400
#define HALF_PERMIT_VALUE_ENCODER				200
#define MIN_PERMIT_VALUE_ENCODER				58
#define STEP_VALUE_ENCODER						4
#define MAX_VALUE_CLICK_ENCODER					100
#define MIN_VALUE_CLICK_ENCODER					15
#define CLOCKWISE								0
#define COUNTERCLOCKWISE						1
#define ROTATE_UP_LIMIT							0xA1B1
#define ROTATE_DOWN_LIMIT						0xA1B2



uint32_t counter = 0;
uint8_t direction = 0;
uint32_t encoderValue = 0;
uint32_t oldEncodValue = 0;


static void waitEncod(void);
static void searchRotation(void);
static void setCounterLimits(void);
static int convertRange(int numValue, int fromLow, int fromHigh, int toLow, int toHigh);



//-----------------------------------------------------------------------------
/**
  * @brief  Reading the state of the encoder. Calculation of the encoder "click" 
  *			counter (range from 15 to 100), or encoder on mode buttons
  * @param  None  
  * @retval None
  */
void tsk_encoder(void)
{
	HAL_TIM_Encoder_Start_IT(&htim1,TIM_CHANNEL_1 | TIM_CHANNEL_2);	
	encodClr();
	encodSetHalfCnt();
	
	while(1)
	{		
		//--- Getting counter value
		counter = __HAL_TIM_GET_COUNTER(&htim1);		
		direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);						
		//--- Setting a ban on reading the encoder value when writing
		setSemaphor(SemEncodBusyHandle);		
		encoderValue = counter/STEP_VALUE_ENCODER;		
		//--- Disable no read value of the encoder when recording
		clrSemaphor(SemEncodBusyHandle);
		direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim1);					
		setCounterLimits();						
		searchRotation();				
		osDelay(1);		
	}
}

//-----------------------------------------------------------------------------
/**
  * @brief  The function returns the current value of the encoder counter. 
  *			Range from 15 to 100. With step 1.
  * @param  None  
  * @retval The current counter value ranges from 15 to 100
  */
uint32_t encodGetValue(void)
{
	waitEncod();
	
	if(encoderValue > MAX_VALUE_CLICK_ENCODER)
	{
		waitEncod();
		encoderValue = MAX_VALUE_CLICK_ENCODER;
	}
	else if(encoderValue <= MIN_VALUE_CLICK_ENCODER)
	{
		waitEncod();
		encoderValue = MIN_VALUE_CLICK_ENCODER;
	}
	
	return encoderValue;
}

//-----------------------------------------------------------------------------
/**
  * @brief  Reset the counter value of the encoder.
  * @param  None  
  * @retval None
  */
void encodClr(void)
{
	waitEncod();	
	TIM1->CNT = MIN_PERMIT_VALUE_ENCODER;
	counter = MIN_PERMIT_VALUE_ENCODER;
}

//-----------------------------------------------------------------------------
/**
  * @brief  The function waits for the encoder counter value to be recorded. 
  *			For protection from reading incorrect values of the counter.
  * @param  None  
  * @retval None
  */
static void waitEncod(void)
{
	while(getSemaphor(SemEncodBusyHandle))
	{
		osDelay(5);
	}
}

//-----------------------------------------------------------------------------
/**
  * @brief  Determines whether the encoder has been rotated and in which direction.
  *			Function to use for the rotation of the encoder as a button. In the case
  *			of the encoder turns clockwise or counter-clockwise sets the appropriate semaphore.
  * @param  None  
  * @retval None
  */
static void searchRotation(void)
{			
	if((oldEncodValue < counter))												//--- Clockwise rotation
	{
		clrSemaphor(SemEncoderDownHandle);
		setSemaphor(SemEncoderUpHandle);		
	}	
	else if((oldEncodValue > counter))											//--- Counterclockwise rotation
	{
		clrSemaphor(SemEncoderUpHandle);
		setSemaphor(SemEncoderDownHandle);
	}
	else																		//--- No rotation
	{
		clrSemaphor(SemEncoderUpHandle);
		clrSemaphor(SemEncoderDownHandle);
	}
		
	oldEncodValue = counter;	
}

//-----------------------------------------------------------------------------
/**
  * @brief  Setting the permissible limits of the encoder counter. Limit "jump" 
  *			from 15 to 100 when rotating counterclockwise. Limit "jump" from 100 to 15 
  *			when rotating clockwise
  * @param  None  
  * @retval None
  */
static void setCounterLimits(void)
{	
	if(counter >= (MAX_PERMIT_VALUE_ENCODER + 1))
	{						
		TIM1->CNT = MAX_PERMIT_VALUE_ENCODER;
		counter = MAX_PERMIT_VALUE_ENCODER;			
	}						
	else if(counter <= MIN_PERMIT_VALUE_ENCODER)
	{						
		TIM1->CNT = MIN_PERMIT_VALUE_ENCODER + STEP_VALUE_ENCODER;
		counter = MIN_PERMIT_VALUE_ENCODER + STEP_VALUE_ENCODER;
	}		
}

//-----------------------------------------------------------------------------
/**
  * @brief  For correcly work in menu. When the encoder counter is overfilled,
  *			a one "click" in the opposite direction occurs
  * @param  None  
  * @retval None
  */
void encodSetHalfCnt(void)
{
	TIM1->CNT = HALF_PERMIT_VALUE_ENCODER;	
	counter = HALF_PERMIT_VALUE_ENCODER;
	encoderValue = 50;
}
	
//-----------------------------------------------------------------------------
/**
  * @brief  Set encoder value
  * @param  @arg val - value encoder, range from 0 to 100 
  * @retval None
  */
void encodSetValue(uint32_t val)
{
	uint32_t convertVal = 0;
	
	
	convertVal = convertRange(val, 0, 100, 0, 400);
	TIM1->CNT = convertVal;	
	counter = convertVal;
	encoderValue = val;
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


