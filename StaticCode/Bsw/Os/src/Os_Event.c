#include "Os_Event.h"
#include "Os_Task.h"
#include "Os_Types.h"
#include "Os_Queue.h"

extern volatile int Os_ISR_Level;
extern volatile bool Os_DeferredSchedule;

StatusType Os_SetEvent(TaskType TaskID, EventMaskType Mask) {
    if (TaskID >= NUMBER_OF_TASKS) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_TaskControlBlockType* t = &Os_TaskTable[TaskID];
    if (t->TaskType != TASK_EXTENDED) {
        OS_LOG("ClearEvent: Task %d is Basic Task don't has event to set", t->TaskID);
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }

    t->EventMask |= Mask;

    if (t->TaskState == WAITING && (t->EventMask & t->WaitMask)) {
        OS_LOG("Event active task %d", TaskID);
        t->TaskState = READY;
        t->WaitMask = 0;
        ReadyQueuePush(TaskID);
        if (Os_ISR_Level > 0) {
            Os_DeferredSchedule = true;
        } else {
            Os_Schedule();
        }
    }

    return E_OK;
}

StatusType ClearEvent(EventMaskType Mask) {
    if (INVALID_TASK == Os_RunningTask) {
        OS_LOG("ClearEvent: No task is running for clear event");
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }
    Os_TaskControlBlockType* t = &Os_TaskTable[Os_RunningTask];
    if (t->TaskType != TASK_EXTENDED) {
        OS_LOG("ClearEvent: Task %d is Basic Task don't has event to clear", t->TaskID);
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }

    t->EventMask &= ~Mask;
    return E_OK;
}

StatusType GetEvent(TaskType TaskID, EventMaskType *Mask) {
    if (NULL_PTR == Mask) {
        CALL_ERROR_HOOK(E_OS_PARAM_POINTER);
        return E_OS_PARAM_POINTER;
    }
    if (TaskID >= NUMBER_OF_TASKS) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_TaskControlBlockType* t = &Os_TaskTable[TaskID];
    *Mask = t->EventMask;

    return E_OK;
}

StatusType WaitEvent(EventMaskType Mask) {
    Os_TaskControlBlockType* t = &Os_TaskTable[Os_RunningTask];
    if (t->TaskType != TASK_EXTENDED) {
        OS_LOG("ClearEvent: Task %d is Basic Task don't has event to wait", t->TaskID);
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }

    if (t->EventMask & Mask) {
        return E_OK;
    }

    t->WaitMask = Mask;
    t->TaskState = WAITING;
    Os_RunningTask = INVALID_TASK;
    OS_LOG("WaitEvent: Task %d is waiting a event", t->TaskID);
    Os_Schedule();

    return E_OK;
}
