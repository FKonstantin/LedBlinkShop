#ifndef _ENCODER_H_
#define _ENCODER_H_


#include "cmsis_os.h"


void tsk_encoder(void);
uint32_t encodGetValue(void);
void encodClr(void);
void encodSetHalfCnt(void);
void encodSetValue(uint32_t val);






#endif //_ENCODER_H_













