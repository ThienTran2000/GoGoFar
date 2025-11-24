#include "Os.h"
#include "Os_Cfg.h"

void Os_TaskInit_Entry(void)
{
    TerminateTask();
}

void Os_TaskTiming10ms_Entry(void)
{
    TerminateTask();
}

void Os_TaskEvent20ms_Entry(void)
{
    while (1)
    {
        WaitEvent(Os_Event20ms);
        ClearEvent(Os_Event20ms);
        // Event handling code
    }
    
    TerminateTask();
}
