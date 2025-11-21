#include "HardwareSpecific.h"
#include "Platform_Types.h"

/* Define maximum isr handler */
#define OS_ISR_MAX_VECTORS 32

#pragma section ".IsrRamTable_Cpu0" aw 4
IsrHandler IsrRamTable_Cpu0[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu1" aw 4
IsrHandler IsrRamTable_Cpu1[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu2" aw 4
IsrHandler IsrRamTable_Cpu2[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu3" aw 4
IsrHandler IsrRamTable_Cpu3[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu4" aw 4
IsrHandler IsrRamTable_Cpu4[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu5" aw 4
IsrHandler IsrRamTable_Cpu5[OS_ISR_MAX_VECTORS];
#pragma section

#pragma section ".IsrRamTable_Cpu6" aw 4
IsrHandler IsrRamTable_Cpu6[OS_ISR_MAX_VECTORS];
#pragma section

/* This method help we can modify interrupt handler in runtime */
#define BSP_ISR_VECTOR_TABLE(i) \
    __asm (".section .isr_vector_table_cpu" #i " , \"ax\", @progbits"); \
    __asm (".align 11"); \
    __asm (".global __INTTAB_CPU" #i); \
    __asm ("__INTTAB_CPU" #i ":")

#define BSP_ISR_DEFINE_HANDLER(cpu, i) \
    __asm (".align 5"); \
    __asm ("bisr " #i); \
    __asm ("movh.a %a14, hi:(IsrRamTable_Cpu" #cpu "+ 4 * " #i ")"); \
    __asm ("lea    %a14, [%a14]lo:(IsrRamTable_Cpu" #cpu "+ 4 * " #i ")"); \
    __asm ("ld.a   %a14, [%a14]0"); \
    __asm ("calli  %a14"); \
    __asm ("rslcx"); \
    __asm ("rfe");

#define ISR_HANDLER_DEFINE(cpu) \
    BSP_ISR_VECTOR_TABLE(cpu); \
    BSP_ISR_DEFINE_HANDLER(cpu, 0);\
    BSP_ISR_DEFINE_HANDLER(cpu, 1);\
    BSP_ISR_DEFINE_HANDLER(cpu, 2);\
    BSP_ISR_DEFINE_HANDLER(cpu, 3);\
    BSP_ISR_DEFINE_HANDLER(cpu, 4);\
    BSP_ISR_DEFINE_HANDLER(cpu, 5);\
    BSP_ISR_DEFINE_HANDLER(cpu, 6);\
    BSP_ISR_DEFINE_HANDLER(cpu, 7);\
    BSP_ISR_DEFINE_HANDLER(cpu, 8);\
    BSP_ISR_DEFINE_HANDLER(cpu, 9);\
    BSP_ISR_DEFINE_HANDLER(cpu, 10);\
    BSP_ISR_DEFINE_HANDLER(cpu, 11);\
    BSP_ISR_DEFINE_HANDLER(cpu, 12);\
    BSP_ISR_DEFINE_HANDLER(cpu, 13);\
    BSP_ISR_DEFINE_HANDLER(cpu, 14);\
    BSP_ISR_DEFINE_HANDLER(cpu, 15);\
    BSP_ISR_DEFINE_HANDLER(cpu, 16);\
    BSP_ISR_DEFINE_HANDLER(cpu, 17);\
    BSP_ISR_DEFINE_HANDLER(cpu, 18);\
    BSP_ISR_DEFINE_HANDLER(cpu, 19);\
    BSP_ISR_DEFINE_HANDLER(cpu, 20);\
    BSP_ISR_DEFINE_HANDLER(cpu, 21);\
    BSP_ISR_DEFINE_HANDLER(cpu, 22);\
    BSP_ISR_DEFINE_HANDLER(cpu, 23);\
    BSP_ISR_DEFINE_HANDLER(cpu, 24);\
    BSP_ISR_DEFINE_HANDLER(cpu, 25);\
    BSP_ISR_DEFINE_HANDLER(cpu, 26);\
    BSP_ISR_DEFINE_HANDLER(cpu, 27);\
    BSP_ISR_DEFINE_HANDLER(cpu, 28);\
    BSP_ISR_DEFINE_HANDLER(cpu, 29);\
    BSP_ISR_DEFINE_HANDLER(cpu, 30);\
    BSP_ISR_DEFINE_HANDLER(cpu, 31);

/* Start define interrupt table */
ISR_HANDLER_DEFINE(0);
ISR_HANDLER_DEFINE(1);
ISR_HANDLER_DEFINE(2);
ISR_HANDLER_DEFINE(3);
ISR_HANDLER_DEFINE(4);
ISR_HANDLER_DEFINE(5);
#pragma section

void Isr_RegisterIsrHandler(IsrHandler isr, uint8 vectabNum, uint8 prio)
{
    switch (vectabNum)
    {
    case 0:
        IsrRamTable_Cpu0[prio] = isr;
        break;
    case 1:
        IsrRamTable_Cpu1[prio] = isr;
        break;
    case 2:
        IsrRamTable_Cpu2[prio] = isr;
        break;
    case 3:
        IsrRamTable_Cpu3[prio] = isr;
        break;
    case 4:
        IsrRamTable_Cpu4[prio] = isr;
        break;
    case 5:
        IsrRamTable_Cpu5[prio] = isr;
        break;
    default:
        break;
    }
}

/*****************************TRAP********************************/

/* TRAP Vector table definition macro */
#define TRAP_VECTOR_TABLE(i) \
    __asm (".section .trap_vector_table" #i " , \"ax\", @progbits"); \
    __asm (".align 8"); \
    __asm (".global __TRAPTAB_CPU" #i); \
    __asm ("__TRAPTAB_CPU" #i ":")

/* TRAP Vector X */
#define TRAP_HANDLER(i, handler)  \
    __asm (".align 5"); \
    __asm ("debug"); \
    __asm ("svlcx"); \
    __asm ("movh.a %a14, hi:" #handler); \
    __asm ("lea    %a14, [%a14]lo:" #handler); \
    __asm ("ji %a14")

#define TRAP_CLASS_DEFINE \
    TRAP_HANDLER(0, trap_MMU_Handler);
    TRAP_HANDLER(1, trap_internalProtection_Handler);
    TRAP_HANDLER(2, trap_instruction_Handler);
    TRAP_HANDLER(3, trap_context_handler);
    TRAP_HANDLER(4, trap_sysBus_handler);
    TRAP_HANDLER(5, trap_assertion_handler);
    TRAP_HANDLER(6, trap_sysCall_handler);
    TRAP_HANDLER(7, trap_nonMaskAbleIsr_handler);
    TRAP_HANDLER(8, trap_debug_handler);
#define TRAP_VECTOR_TABLE_DEFINION(i) \
    TRAP_VECTOR_TABLE(i); \
    TRAP_CLASS_DEFINE \

/* Define trap table */
TRAP_VECTOR_TABLE_DEFINION(0);
#pragma section
TRAP_VECTOR_TABLE_DEFINION(1);
#pragma section
TRAP_VECTOR_TABLE_DEFINION(2);
#pragma section
TRAP_VECTOR_TABLE_DEFINION(3);
#pragma section
TRAP_VECTOR_TABLE_DEFINION(4);
#pragma section
TRAP_VECTOR_TABLE_DEFINION(5);
#pragma section


#pragma section ".trap_handlers" ax 2
void trap_MMU_Handler(void)
{

}

void trap_internalProtection_Handler(void)
{

}

void trap_instruction_Handler(void)
{

}

void trap_context_handler(void)
{

}

void trap_sysBus_handler(void)
{

}

void trap_assertion_handler(void)
{

}

void trap_sysCall_handler(void)
{

}

void trap_nonMaskAbleIsr_handler(void)
{

}

void trap_debug_handler(void)
{

}
#pragma section





