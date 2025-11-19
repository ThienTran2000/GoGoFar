#include "Os.h"
#include "Os_Cfg.h"
#include <windows.h>

VOID CALLBACK TimerProc(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
    CounterTickHandler(CounterHardwareTimer);
}

int main(void) {
    HANDLE hTimer = NULL;
    CreateTimerQueueTimer(&hTimer, NULL, TimerProc, NULL, 10, 10, WT_EXECUTEDEFAULT);

    StartOS(OSDEFAULTAPPMODE);
    return 0;
}
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
