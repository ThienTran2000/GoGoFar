
#include "Os_Porting.h"
#include "IfxStm.h"
#include "Ifx_Ssw_Infra.h"
#include "Os_Counter.h"
#include "HardwareSpecific.h"

#define STM_ISR_PRIORITY 1
#define MODULE_STM0_TICKS_PER_MILISECOND 100000U

typedef struct
{
    uint32 PCXI;
    uint32 PSW;
    uint32 SP;
    uint32 RA;
    uint32 D8;
    uint32 D9;
    uint32 D10;
    uint32 D11;
    uint32 A12;
    uint32 A13;
    uint32 A14;
    uint32 A15;
    uint32 D12;
    uint32 D13;
    uint32 D14;
    uint32 D15;
}upperCSAType;

void isrSTM_0(void);

void Os_InitContext(Os_TaskContextType* ctx, StackType* stack_pst, void* entryFunctionPtr)
{
    uint16 index_u16;
    uint32 nextCxi;
    uint32* nxtCsa;
    uint32* preCsa;
    /* Init CSA chain */
    nxtCsa = stack_pst->csa_pu8;
    for ( index_u16 = 0; index_u16 < stack_pst->csaSize_u32; index_u16++ )
    {
        nextCxi = ((uint32)((uint32)nxtCsa & ((uint32)0XFU << 28U)) >> 12U) | \
                      ((uint32)((uint32)nxtCsa & ((uint32)0XFFFFU << 6U)) >> 6U);
        if ( 0u == index_u16 )
        {
            ctx->PCXI = nextCxi;
        }
        else
        {
            if ( 1u == index_u16 )
            {
                ctx->FCX = nextCxi;
            }
            *preCsa = nextCxi;
        }
        if ( (stack_pst->csaSize_u32 - 3) == index_u16 )
        {
            ctx->LCX = nextCxi;
        }
        preCsa = nxtCsa;
        nxtCsa += 16; /* Skip 64bytes CSA */
    }
    /* Init SP and RA for first CSA */
    /* Growdown type */
    ((upperCSAType*)stack_pst->csa_pu8)->SP = (uint32)(&stack_pst->ustack_pu8[stack_pst->ustackSize_u32]);
    ((upperCSAType*)stack_pst->csa_pu8)->RA = (uint32)entryFunctionPtr;
}

void Os_ResetContext(Os_TaskContextType* ctx, StackType* stack_pst, void* entryFunctionPtr)
{
    uint32* curCsa;
    curCsa = stack_pst->csa_pu8;
    ctx->PCXI = ((uint32)((uint32)curCsa & ((uint32)0XFU << 28U)) >> 12U) | \
                      ((uint32)((uint32)curCsa & ((uint32)0XFFFFU << 6U)) >> 6U);
    curCsa += 16u;
    ctx->FCX = ((uint32)((uint32)curCsa & ((uint32)0XFU << 28U)) >> 12U) | \
                      ((uint32)((uint32)curCsa & ((uint32)0XFFFFU << 6U)) >> 6U);
    ((upperCSAType*)stack_pst->csa_pu8)->SP = (uint32)(&stack_pst->ustack_pu8[stack_pst->ustackSize_u32]);
    ((upperCSAType*)stack_pst->csa_pu8)->RA = (uint32)entryFunctionPtr;
}
void IsrInit_STM(void)
{
    Isr_RegisterIsrHandler(isrSTM_0, 0, STM_ISR_PRIORITY);
    /* Config comparator 0 */
    MODULE_STM0.CMCON.B.MSIZE0 = 31u;                                                                       /* Use 31bit to compare */
    MODULE_STM0.CMCON.B.MSTART0 = 0u;                                                                       /* Start compare from bit 0 */
    MODULE_STM0.ICR.B.CMP0OS = IfxStm_ComparatorInterrupt_ir0;                                              /* Generate interrupt source 0 */
    /* Config interrupt, use src 0 of stm0 */
    (MODULE_SRC.STM.STM[0u].SR[0]).B.SRPN = STM_ISR_PRIORITY;                                               /* ISR priority */
    (MODULE_SRC.STM.STM[0u].SR[0]).B.TOS = IfxSrc_Tos_cpu0;                                                 /* Trigger isr on core0 */
    (MODULE_SRC.STM.STM[0u].SR[0]).B.CLRR = 1u;                                                             /* Clear source request */
    (MODULE_SRC.STM.STM[0u].SR[0]).B.SRE = 1u;                                                              /* Enable this resource */
    MODULE_STM0.CMP[IfxStm_Comparator_0].U = MODULE_STM0.TIM0.U;                                            /* Avoid interrupt when config */
    MODULE_STM0.ISCR.B.CMP0IRR = 0u;                                                                        /* Clear isr flag */
    MODULE_STM0.ICR.B.CMP0EN = 0u;                                                                          /* Enable interrupt */
    MODULE_STM0.CMP[IfxStm_Comparator_0].U = MODULE_STM0.TIM0.U + MODULE_STM0_TICKS_PER_MILISECOND;         /* Interrupt in 1ms */
}

/* CAT1 ISR */
void isrSTM_0(void)
{
    MODULE_STM0.CMP[IfxStm_Comparator_0].U = MODULE_STM0.TIM0.U + MODULE_STM0_TICKS_PER_MILISECOND;
    IncrementCounter(CounterHardwareTimer);
}

void OsStartSlaveCore(uint8 coreId, uint32 EntryAddr)
{
    uint32 cpu;
    cpu = (uint32)(&MODULE_CPU0) + 0x20000 * coreId;
    Ifx_Ssw_startCore((Ifx_CPU*)cpu, EntryAddr);
}



