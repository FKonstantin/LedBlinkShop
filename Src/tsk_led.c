#include "tsk_led.h"
#include "semaphores.h"
#include "led_run_blink.h"
#include "led_on_all.h"
#include "led_all_blink.h"
#include "led_1_4_8_12_16_blinl.h"
#include "led_runing_1.h"
#include "led_demo.h"



//-----------------------------------------------------------------------------
void tsk_led(void)
{
	while(1)
	{
		if(getSemaphor(SemLedMode1Handle))
			ledRunBlink();
		else if(getSemaphor(SemLedMode2Handle))
			ledOnAll();			
		else if(getSemaphor(SemLedMode3Handle))
			ledAllBlink();			
		else if(getSemaphor(SemLedMode4Handle))
			led1_4Blink();
		else if(getSemaphor(SemLedMode5Handle))
			ledRuning1();
		else if(getSemaphor(SemLedMode6Handle))		
			ledDemo();
		
		osDelay(50);
	}
}










