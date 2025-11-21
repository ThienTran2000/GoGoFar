#ifndef __OS_PORTING_H__
#define __OS_PORTING_H__

#include "Platform_Types.h"
#include "Compilers.h"

/* Define type */
typedef struct
{
    uint32 PCXI;
    uint32 FCX;
    uint32 LCX;
} Os_TaskContextType;

void Os_SaveContext(Os_TaskContextType* ctx);
void Os_RestoreContext(Os_TaskContextType* ctx);
void Os_InitContext(Os_TaskContextType* ctx, uint32* ustack_pu32, uint16 uStackSize_16, uint32* csa_pu32, uint16 callDeep_u16, void* entryFunctionPtr);
void OsStartSlaveCore(uint8 coreId, uint32 EntryAddr);
void IsrInit_STM(void);

#endif