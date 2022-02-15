/*
* led_run_blink - LED_MODE_1 - SemLedMode1
*/


#include "led_run_blink.h"
#include "stm32f1xx_hal.h"
#include "tsk_main.h"
#include "semaphores.h"
#include <stdbool.h>


static bool delayWithSemaphor(uint32_t timeDivisionOn10);



//-----------------------------------------------------------------------------
void ledRunBlink()
{
	while(1)
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
}

//-----------------------------------------------------------------------------
static bool delayWithSemaphor(uint32_t timeDivisionOn10)
{
	for(int i = 0; i < timeDivisionOn10; i++)
	{
		if(!getSemaphor(SemLedMode1Handle))		
			return true;
		
		osDelay(10);
	}
	
	return false;
}








