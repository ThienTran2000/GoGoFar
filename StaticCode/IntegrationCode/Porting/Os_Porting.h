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

typedef struct
{
    uint8* ustack_pu8;
    uint32 ustackSize_u32;
    uint8* csa_pu8;
    uint32 csaSize_u32;
} StackType;

void Os_SaveContext(Os_TaskContextType* ctx);
void Os_RestoreContext(Os_TaskContextType* ctx);
void Os_InitContext(Os_TaskContextType* ctx, StackType* stack_pst, void* entryFunctionPtr);
void Os_ResetContext(Os_TaskContextType* ctx, StackType* stack_pst, void* entryFunctionPtr);
void OsStartSlaveCore(uint8 coreId, uint32 EntryAddr);
void IsrInit_STM(void);

#endif