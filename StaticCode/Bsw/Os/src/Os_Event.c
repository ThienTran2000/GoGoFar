#include "Os_Event.h"
#include "Os_Task.h"
#include "Os_Types.h"
#include "Os_Queue.h"

StatusType Os_SetEvent(TaskType TaskID, EventMaskType Mask) {
    if (TaskID >= NUMBER_OF_TASKS) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_TaskControlBlockType* t = &Os_TaskTable[TaskID];
    if (t->TaskType != TASK_EXTENDED) {
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }

    t->EventMask |= Mask;

    if (t->TaskState == WAITING && (t->EventMask & t->WaitMask)) {
        t->TaskState = READY;
        t->WaitMask = 0;
    }

    return E_OK;
}

StatusType ClearEvent(EventMaskType Mask) {
    Os_TaskControlBlockType* t = &Os_TaskTable[Os_RunningTask];
    if (t->TaskType != TASK_EXTENDED) {
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
        CALL_ERROR_HOOK(E_OS_ACCESS);
        return E_OS_ACCESS;
    }

    if (t->EventMask & Mask) {
        return E_OK;
    }

    t->WaitMask = Mask;
    t->TaskState = WAITING;
    ReadyQueueRemove(t);
    Schedule();

    return E_OK;
}
