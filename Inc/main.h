/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define Led14_Pin GPIO_PIN_1
#define Led14_GPIO_Port GPIOA
#define BtnUp_Pin GPIO_PIN_2
#define BtnUp_GPIO_Port GPIOA
#define BtnDown_Pin GPIO_PIN_3
#define BtnDown_GPIO_Port GPIOA
#define BtnLeft_Pin GPIO_PIN_4
#define BtnLeft_GPIO_Port GPIOA
#define BtnRight_Pin GPIO_PIN_5
#define BtnRight_GPIO_Port GPIOA
#define Led16_Pin GPIO_PIN_6
#define Led16_GPIO_Port GPIOA
#define Led15_Pin GPIO_PIN_7
#define Led15_GPIO_Port GPIOA
#define Led14B0_Pin GPIO_PIN_0
#define Led14B0_GPIO_Port GPIOB
#define Led13_Pin GPIO_PIN_1
#define Led13_GPIO_Port GPIOB
#define Led12_Pin GPIO_PIN_10
#define Led12_GPIO_Port GPIOB
#define Led11_Pin GPIO_PIN_11
#define Led11_GPIO_Port GPIOB
#define Led10_Pin GPIO_PIN_12
#define Led10_GPIO_Port GPIOB
#define Led9_Pin GPIO_PIN_13
#define Led9_GPIO_Port GPIOB
#define Led8_Pin GPIO_PIN_14
#define Led8_GPIO_Port GPIOB
#define Led7_Pin GPIO_PIN_15
#define Led7_GPIO_Port GPIOB
#define EncoderDT_Pin GPIO_PIN_8
#define EncoderDT_GPIO_Port GPIOA
#define EncoderCLK_Pin GPIO_PIN_9
#define EncoderCLK_GPIO_Port GPIOA
#define Led6_Pin GPIO_PIN_11
#define Led6_GPIO_Port GPIOA
#define Led5_Pin GPIO_PIN_12
#define Led5_GPIO_Port GPIOA
#define Led4_Pin GPIO_PIN_15
#define Led4_GPIO_Port GPIOA
#define Led3_Pin GPIO_PIN_3
#define Led3_GPIO_Port GPIOB
#define Led2_Pin GPIO_PIN_4
#define Led2_GPIO_Port GPIOB
#define Led1_Pin GPIO_PIN_5
#define Led1_GPIO_Port GPIOB
#define PwmSignal_Pin GPIO_PIN_8
#define PwmSignal_GPIO_Port GPIOB
#define BtnEncod_Pin GPIO_PIN_9
#define BtnEncod_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
