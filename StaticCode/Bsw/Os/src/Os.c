#include "Os.h"

extern void ReadyQueueInit(ReadyQueueType* q);
extern ReadyQueueType ReadyQueue[];
boolean Os_Running = FALSE;

StatusType GetActiveApplicationMode(AppModeType *Mode) {
    *Mode = OSDEFAULTAPPMODE;
    return E_OK;
}

StatusType StartOS(AppModeType mode)
{
    uint16 idx;
    OS_LOG("StartOS: AppMode=%d", mode);

    Os_Running = TRUE;

    for (uint8 prio = 0; prio < MAX_PRIORITY; prio++) {
        ReadyQueueInit(&ReadyQueue[prio]);
    }

    OS_LOG("StartOS: Activating autostart alarms and tasks...");
    Os_ActivateAutoStartAlarms();
    Os_ActivateAutoStartTasks();

#ifdef USESTARTUPHOOK
    STARTUP_HOOK_FUNCTION();
#endif
    for ( idx = 0u; idx < NUMBER_OF_TASKS; idx++ )
    {
        Os_InitContext(&(Os_TaskTable[idx].Context), &(Os_TaskTable->Stack), Os_TaskTable->Entry);
    }
    Schedule();

    // Should never reach here
    return E_OK;
}

void ShutdownOS(StatusType Error)
{
    OS_LOG("ShutdownOS: Shutting down OSEK OS (Error=0x%02X)...\n", Error);

#ifdef USESHUTDOWNHOOK
    SHUTDOWN_HOOK_FUNCTION(Error);
#endif

    Os_Running = FALSE;
    Os_RunningTask = INVALID_TASK;

    for (uint8 prio = 0; prio < MAX_PRIORITY; prio++) {
        ReadyQueueInit(&ReadyQueue[prio]);
    }

    OS_LOG("ShutdownOS: OS stopped. Entering idle state.");

    Os_IdleTask();
}
