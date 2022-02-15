/*
* led_on_all - LED_MODE_2 - SemLedMode2
*/


#include "led_on_all.h"
#include "semaphores.h"
#include "stm32f1xx_hal.h"



//-----------------------------------------------------------------------------
void ledOnAll()
{
	while(getSemaphor(SemLedMode2Handle))
	{
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
		osDelay(20);
	}
}






