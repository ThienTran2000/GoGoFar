#include "Os_Cfg.h"

uint32 Os_ustack_taskinit_buf[OS_USTACK_TASKINIT_SIZE / 32];
uint32 Os_ustack_tasktiming10ms_buf[OS_USTACK_TASKTIMING10MS_SIZE / 32];
uint32 Os_ustack_taskevent20ms_buf[OS_USTACK_TASKEVENT20MS_SIZE / 32];

uint64 Os_csa_taskinit_buf[OS_CSA_TASKINIT_CALLDEEPTH / 64];
uint64 Os_csa_tasktiming10ms_buf[OS_CSA_TASKTIMING10MS_CALLDEEPTH / 64];
uint64 Os_csa_taskevent20ms_buf[OS_CSA_TASKEVENT20MS_CALLDEEPTH / 64];