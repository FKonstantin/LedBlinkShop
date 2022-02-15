#ifndef _SEMAPHORES_
#define _SEMAPHORES_


#include "cmsis_os.h"

//--- To work with this library, you need to specify here as "external" semaphores
extern osSemaphoreId SemBtnUpHandle;
extern osSemaphoreId SemBtnDownHandle;
extern osSemaphoreId SemBtnLeftHandle;
extern osSemaphoreId SemBtnRightHandle;
extern osSemaphoreId SemBtnOkHandle;
extern osSemaphoreId SemBtnEscHandle; 
extern osSemaphoreId SemLcdLine1Handle;
extern osSemaphoreId SemLcdLine2Handle;
extern osSemaphoreId SemLcdLine3Handle; 
extern osSemaphoreId SemLcdLine4Handle;
extern osSemaphoreId SemLcdRedrawMenuHandle;
extern osSemaphoreId SemLcdExitMenuHandle; 
extern osSemaphoreId SemEncodBusyHandle; 
extern osSemaphoreId SemEncoderUpHandle; 
extern osSemaphoreId SemEncoderDownHandle; 
extern osSemaphoreId SemLedMode1Handle;
extern osSemaphoreId SemLedMode2Handle;
extern osSemaphoreId SemLedMode3Handle;
extern osSemaphoreId SemLedMode4Handle;
extern osSemaphoreId SemLedMode5Handle;
extern osSemaphoreId SemLedMode6Handle;
extern osSemaphoreId SemLedMode7Handle;
extern osSemaphoreId SemLedMode8Handle;
extern osSemaphoreId SemLedMode9Handle; 
extern osSemaphoreId SemLedMode10Handle;
extern osSemaphoreId SemBtnEncodHandle;


int getSemaphor(osSemaphoreId semHandle);
void setSemaphor(osSemaphoreId semHandle);
void clrSemaphor(osSemaphoreId semHandle);
void semInit(void);











#endif





















