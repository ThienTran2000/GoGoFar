#ifndef __ISR_H__
#define __ISR_H__

#include "Platform_Types.h"

typedef void (*IsrHandler)(void);

void Isr_RegisterIsrHandler(IsrHandler isr, uint8 vectabNum, uint8 prio);

#endif