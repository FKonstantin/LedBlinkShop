/**
  ******************************************************************************
  * File Name          : semaphores.c
  * Description        : The library was created to simplify working with 
  *                      semaphores as with flags.  
  ******************************************************************************
  */
  
#include "semaphores.h"



//-----------------------------------------------------------------------------
/**
  * @brief  Request semaphore status
  * @param  semHandle - Semaphore handler
  * @retval Semaphore status
  *			@arg 0 - Semaphore not set
  *			@arg non zero - Semaphore set
  */
int getSemaphor(osSemaphoreId semHandle)
{
	return osSemaphoreGetCount(semHandle);
}

//-----------------------------------------------------------------------------
/**
  * @brief  Sets the semaphore
  * @param  semHandle - Semaphore handler
  * @retval None
*/
void setSemaphor(osSemaphoreId semHandle)
{
	osSemaphoreRelease(semHandle);
}
//-----------------------------------------------------------------------------
/**
  * @brief  Clear the semaphore
  * @param  SemHandle - Semaphore handler
  * @retval None
*/
void clrSemaphor(osSemaphoreId semHandle)
{
	osSemaphoreWait(semHandle, 100);
}

//-----------------------------------------------------------------------------
void semInit(void)
{
	clrSemaphor(SemBtnUpHandle);
	clrSemaphor(SemBtnDownHandle);
	clrSemaphor(SemBtnLeftHandle);
	clrSemaphor(SemBtnRightHandle);	
	clrSemaphor(SemLcdLine1Handle);
	clrSemaphor(SemLcdLine2Handle);
	clrSemaphor(SemLcdLine3Handle); 
	clrSemaphor(SemLcdLine4Handle);
	clrSemaphor(SemLcdRedrawMenuHandle);
	clrSemaphor(SemLcdExitMenuHandle); 
	clrSemaphor(SemEncodBusyHandle); 
	clrSemaphor(SemEncoderUpHandle); 
	clrSemaphor(SemEncoderDownHandle); 	
	clrSemaphor(SemLedMode1Handle);
	clrSemaphor(SemLedMode2Handle);
	clrSemaphor(SemLedMode3Handle);
	clrSemaphor(SemLedMode4Handle);
	clrSemaphor(SemLedMode5Handle);
	clrSemaphor(SemLedMode6Handle);
	clrSemaphor(SemLedMode7Handle);
	clrSemaphor(SemLedMode8Handle);
	clrSemaphor(SemLedMode9Handle);
	clrSemaphor(SemLedMode10Handle);
	clrSemaphor(SemBtnEncodHandle);
}
















