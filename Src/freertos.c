/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2020 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "tsk_main.h"
#include "tsk_btns.h"
#include "tsk_encoder.h"
#include "tsk_led.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId TskMain_Handle;
osThreadId TskReadBtn_Handle;
osThreadId TskReadEncoder_Handle;
osThreadId TskLedBlink_Handle;
osSemaphoreId SemBtnUpHandle;
osSemaphoreId SemBtnDownHandle;
osSemaphoreId SemBtnLeftHandle;
osSemaphoreId SemBtnRightHandle;
osSemaphoreId SemLcdLine1Handle;
osSemaphoreId SemLcdLine2Handle;
osSemaphoreId SemLcdLine3Handle;
osSemaphoreId SemLcdLine4Handle;
osSemaphoreId SemLcdRedrawMenuHandle;
osSemaphoreId SemLcdExitMenuHandle;
osSemaphoreId SemEncoderUpHandle;
osSemaphoreId SemEncoderDownHandle;
osSemaphoreId SemEncodBusyHandle;
osSemaphoreId SemLedMode1Handle;
osSemaphoreId SemLedMode2Handle;
osSemaphoreId SemLedMode3Handle;
osSemaphoreId SemLedMode4Handle;
osSemaphoreId SemLedMode5Handle;
osSemaphoreId SemLedMode6Handle;
osSemaphoreId SemLedMode7Handle;
osSemaphoreId SemLedMode8Handle;
osSemaphoreId SemLedMode9Handle;
osSemaphoreId SemLedMode10Handle;
osSemaphoreId SemBtnEncodHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void TskMain(void const * argument);
void TskReadBtn(void const * argument);
void TskReadEncoder(void const * argument);
void TskLedBlink(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of SemBtnUp */
  osSemaphoreDef(SemBtnUp);
  SemBtnUpHandle = osSemaphoreCreate(osSemaphore(SemBtnUp), 1);

  /* definition and creation of SemBtnDown */
  osSemaphoreDef(SemBtnDown);
  SemBtnDownHandle = osSemaphoreCreate(osSemaphore(SemBtnDown), 1);

  /* definition and creation of SemBtnLeft */
  osSemaphoreDef(SemBtnLeft);
  SemBtnLeftHandle = osSemaphoreCreate(osSemaphore(SemBtnLeft), 1);

  /* definition and creation of SemBtnRight */
  osSemaphoreDef(SemBtnRight);
  SemBtnRightHandle = osSemaphoreCreate(osSemaphore(SemBtnRight), 1);

  /* definition and creation of SemLcdLine1 */
  osSemaphoreDef(SemLcdLine1);
  SemLcdLine1Handle = osSemaphoreCreate(osSemaphore(SemLcdLine1), 1);

  /* definition and creation of SemLcdLine2 */
  osSemaphoreDef(SemLcdLine2);
  SemLcdLine2Handle = osSemaphoreCreate(osSemaphore(SemLcdLine2), 1);

  /* definition and creation of SemLcdLine3 */
  osSemaphoreDef(SemLcdLine3);
  SemLcdLine3Handle = osSemaphoreCreate(osSemaphore(SemLcdLine3), 1);

  /* definition and creation of SemLcdLine4 */
  osSemaphoreDef(SemLcdLine4);
  SemLcdLine4Handle = osSemaphoreCreate(osSemaphore(SemLcdLine4), 1);

  /* definition and creation of SemLcdRedrawMenu */
  osSemaphoreDef(SemLcdRedrawMenu);
  SemLcdRedrawMenuHandle = osSemaphoreCreate(osSemaphore(SemLcdRedrawMenu), 1);

  /* definition and creation of SemLcdExitMenu */
  osSemaphoreDef(SemLcdExitMenu);
  SemLcdExitMenuHandle = osSemaphoreCreate(osSemaphore(SemLcdExitMenu), 1);

  /* definition and creation of SemEncoderUp */
  osSemaphoreDef(SemEncoderUp);
  SemEncoderUpHandle = osSemaphoreCreate(osSemaphore(SemEncoderUp), 1);

  /* definition and creation of SemEncoderDown */
  osSemaphoreDef(SemEncoderDown);
  SemEncoderDownHandle = osSemaphoreCreate(osSemaphore(SemEncoderDown), 1);

  /* definition and creation of SemEncodBusy */
  osSemaphoreDef(SemEncodBusy);
  SemEncodBusyHandle = osSemaphoreCreate(osSemaphore(SemEncodBusy), 1);

  /* definition and creation of SemLedMode1 */
  osSemaphoreDef(SemLedMode1);
  SemLedMode1Handle = osSemaphoreCreate(osSemaphore(SemLedMode1), 1);

  /* definition and creation of SemLedMode2 */
  osSemaphoreDef(SemLedMode2);
  SemLedMode2Handle = osSemaphoreCreate(osSemaphore(SemLedMode2), 1);

  /* definition and creation of SemLedMode3 */
  osSemaphoreDef(SemLedMode3);
  SemLedMode3Handle = osSemaphoreCreate(osSemaphore(SemLedMode3), 1);

  /* definition and creation of SemLedMode4 */
  osSemaphoreDef(SemLedMode4);
  SemLedMode4Handle = osSemaphoreCreate(osSemaphore(SemLedMode4), 1);

  /* definition and creation of SemLedMode5 */
  osSemaphoreDef(SemLedMode5);
  SemLedMode5Handle = osSemaphoreCreate(osSemaphore(SemLedMode5), 1);

  /* definition and creation of SemLedMode6 */
  osSemaphoreDef(SemLedMode6);
  SemLedMode6Handle = osSemaphoreCreate(osSemaphore(SemLedMode6), 1);

  /* definition and creation of SemLedMode7 */
  osSemaphoreDef(SemLedMode7);
  SemLedMode7Handle = osSemaphoreCreate(osSemaphore(SemLedMode7), 1);

  /* definition and creation of SemLedMode8 */
  osSemaphoreDef(SemLedMode8);
  SemLedMode8Handle = osSemaphoreCreate(osSemaphore(SemLedMode8), 1);

  /* definition and creation of SemLedMode9 */
  osSemaphoreDef(SemLedMode9);
  SemLedMode9Handle = osSemaphoreCreate(osSemaphore(SemLedMode9), 1);

  /* definition and creation of SemLedMode10 */
  osSemaphoreDef(SemLedMode10);
  SemLedMode10Handle = osSemaphoreCreate(osSemaphore(SemLedMode10), 1);

  /* definition and creation of SemBtnEncod */
  osSemaphoreDef(SemBtnEncod);
  SemBtnEncodHandle = osSemaphoreCreate(osSemaphore(SemBtnEncod), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of TskMain_ */
  osThreadDef(TskMain_, TskMain, osPriorityNormal, 0, 128);
  TskMain_Handle = osThreadCreate(osThread(TskMain_), NULL);

  /* definition and creation of TskReadBtn_ */
  osThreadDef(TskReadBtn_, TskReadBtn, osPriorityNormal, 0, 128);
  TskReadBtn_Handle = osThreadCreate(osThread(TskReadBtn_), NULL);

  /* definition and creation of TskReadEncoder_ */
  osThreadDef(TskReadEncoder_, TskReadEncoder, osPriorityNormal, 0, 128);
  TskReadEncoder_Handle = osThreadCreate(osThread(TskReadEncoder_), NULL);

  /* definition and creation of TskLedBlink_ */
  osThreadDef(TskLedBlink_, TskLedBlink, osPriorityNormal, 0, 128);
  TskLedBlink_Handle = osThreadCreate(osThread(TskLedBlink_), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* TskMain function */
void TskMain(void const * argument)
{

  /* USER CODE BEGIN TskMain */
	/* Infinite loop */
	for(;;)
	{
		tsk_main();
	}
  /* USER CODE END TskMain */
}

/* TskReadBtn function */
void TskReadBtn(void const * argument)
{
  /* USER CODE BEGIN TskReadBtn */
	/* Infinite loop */
	for(;;)
	{
		readBtns();
	}
  /* USER CODE END TskReadBtn */
}

/* TskReadEncoder function */
void TskReadEncoder(void const * argument)
{
  /* USER CODE BEGIN TskReadEncoder */
	/* Infinite loop */
	for(;;)
	{
		tsk_encoder();
	}
  /* USER CODE END TskReadEncoder */
}

/* TskLedBlink function */
void TskLedBlink(void const * argument)
{
  /* USER CODE BEGIN TskLedBlink */
	/* Infinite loop */
	for(;;)
	{
		tsk_led();
	}
  /* USER CODE END TskLedBlink */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
