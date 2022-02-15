#include "tsk_btns.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "semaphores.h"


static void readBtnLeft(void);
static void readBtnRight(void);
static void readBtnDown(void);
static void readBtnUp(void);
static void readBtnEncoder(void);



volatile int btnLeftStateOld = 0;
volatile int btnLeftStateNew = 0;
volatile int btnRightStateOld = 0;
volatile int btnRightStateNew = 0;
volatile int btnDownStateOld = 0;
volatile int btnDownStateNew = 0;
volatile int btnUpStateOld = 0;
volatile int btnUpStateNew = 0;
volatile int btnEncoderStateOld = 0;
volatile int btnEncoderStateNew = 0;




//------------------------------------------------------------------------------
void readBtns(void)
{	
	osDelay(1000);
	
	while(1)
	{
		readBtnLeft();
		readBtnRight();
		readBtnDown();
		readBtnUp();	
		readBtnEncoder();		
	}	
}

//------------------------------------------------------------------------------
static void readBtnLeft(void)
{
	if(HAL_GPIO_ReadPin(BtnLeft_GPIO_Port, BtnLeft_Pin))
        {                                                
            osDelay(50);
            if(!HAL_GPIO_ReadPin(BtnLeft_GPIO_Port, BtnLeft_Pin))
            {                
				return;
            }                                                

            btnLeftStateNew = 1;
            if(btnLeftStateOld == 0)
            {                    
                btnLeftStateOld = 1;
                osDelay(100);
                return;
            }                
            else if(btnLeftStateOld == 1)
            {
                return;
            }                
        } 
        else
        {
            btnLeftStateNew = 0;
            if(btnLeftStateOld == 0)
            {                
				if(!getSemaphor(SemBtnLeftHandle))
                {
                    return; 
                }                                   
								
				osDelay(100);				
				clrSemaphor(SemBtnLeftHandle);
            }
            if(btnLeftStateOld == 1)
            {
                osDelay(100);
                btnLeftStateOld = 0;
                setSemaphor(SemBtnLeftHandle);
            }
        }
}

//------------------------------------------------------------------------------
static void readBtnRight(void)
{	
	if(HAL_GPIO_ReadPin(BtnRight_GPIO_Port, BtnRight_Pin))
        {                                                
            osDelay(50);
            if(!HAL_GPIO_ReadPin(BtnRight_GPIO_Port, BtnRight_Pin))
            {                
				return;
            }                                                

            btnRightStateNew = 1;
            if(btnRightStateOld == 0)
            {                    
                btnRightStateOld = 1;
                osDelay(100);
                return;
            }                
            else if(btnRightStateOld == 1)
            {
                return;
            }                
        } 
        else
        {
            btnRightStateNew = 0;
            if(btnRightStateOld == 0)
            {                
				if(!getSemaphor(SemBtnRightHandle))
                {
                    return; 
                }                                   
								
				osDelay(100);				
				clrSemaphor(SemBtnRightHandle);
            }
            if(btnRightStateOld == 1)
            {
                osDelay(100);
                btnRightStateOld = 0;
                setSemaphor(SemBtnRightHandle);
            }
        }
}	

//------------------------------------------------------------------------------
static void readBtnDown(void)
{
	if(HAL_GPIO_ReadPin(BtnDown_GPIO_Port, BtnDown_Pin))
        {                                                
            osDelay(50);
            if(!HAL_GPIO_ReadPin(BtnDown_GPIO_Port, BtnDown_Pin))
            {                
				return;
            }                                                

            btnDownStateNew = 1;
            if(btnDownStateOld == 0)
            {                    
                btnDownStateOld = 1;
                osDelay(100);
                return;
            }                
            else if(btnDownStateOld == 1)
            {
                return;
            }                
        } 
        else
        {
            btnDownStateNew = 0;
            if(btnDownStateOld == 0)
            {                
				if(!getSemaphor(SemBtnDownHandle))
                {
                    return; 
                }                                   
				
				osDelay(100);				
				clrSemaphor(SemBtnDownHandle);
            }
            if(btnDownStateOld == 1)
            {
                osDelay(100);
                btnDownStateOld = 0;
				setSemaphor(SemBtnDownHandle);	
            }
        }
}

//------------------------------------------------------------------------------
static void readBtnUp(void)
{
	if(HAL_GPIO_ReadPin(BtnUp_GPIO_Port, BtnUp_Pin))
        {                                                
            osDelay(50);
            if(!HAL_GPIO_ReadPin(BtnUp_GPIO_Port, BtnUp_Pin))
            {                
				return;
            }                                                

            btnUpStateNew = 1;
            if(btnUpStateOld == 0)
            {                    
                btnUpStateOld = 1;
                osDelay(100);
                return;
            }                
            else if(btnUpStateOld == 1)
            {
                return;
            }                
        } 
        else
        {
            btnUpStateNew = 0;
            if(btnUpStateOld == 0)
            {                
				if(!getSemaphor(SemBtnUpHandle))
                {
                    return; 
                }                                   
												
				osDelay(100);
				clrSemaphor(SemBtnUpHandle);								
            }
            if(btnUpStateOld == 1)
            {                
                osDelay(100);
				btnUpStateOld = 0;
                setSemaphor(SemBtnUpHandle);						
            }
        }
}

//------------------------------------------------------------------------------
static void readBtnEncoder(void)
{
	//--- Encoder button normaly closed
	if(!HAL_GPIO_ReadPin(BtnEncod_GPIO_Port, BtnEncod_Pin))
        {                                                
            osDelay(50);
            if(HAL_GPIO_ReadPin(BtnEncod_GPIO_Port, BtnEncod_Pin))
            {                
				return;
            }                                                

            btnEncoderStateNew = 1;
            if(btnEncoderStateOld == 0)
            {                    
                btnEncoderStateOld = 1;
                osDelay(100);
                return;
            }                
            else if(btnEncoderStateOld == 1)
            {
                return;
            }              
        } 
        else
        {
            btnEncoderStateNew = 0;
            if(btnEncoderStateOld == 0)
            {                
				if(!getSemaphor(SemBtnEncodHandle))
                {
                    return; 
                }                                   
				osDelay(100);				
				clrSemaphor(SemBtnEncodHandle);
            }
            if(btnEncoderStateOld == 1)
            {
                osDelay(100);
                btnEncoderStateOld = 0;
                setSemaphor(SemBtnEncodHandle);
            }
        }
}













