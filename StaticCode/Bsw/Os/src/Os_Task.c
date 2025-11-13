#include "Os_Task.h"
#include "Os_Queue.h"
#include "Os_Types.h"
#include "Os_Cfg.h"
#include <stdio.h>

Os_TaskControlBlockType Os_TaskTable[NUMBER_OF_TASKS] = {TASK_INIT};
TaskType Os_AutoStartTasks[NUMBER_OF_AUTOSTART_TASKS] = {TASK_AUTOSTART};
TaskType Os_RunningTask = INVALID_TASK;

static void Os_SaveContext(Os_TaskContextType* ctx)
{
    ctx->Os_StackPointer = 0;
    ctx->Os_MSPStackPointer = 0;
}

static void Os_RestoreContext(Os_TaskContextType* ctx)
{
    Os_TaskTable[Os_RunningTask].Entry();
}

void Os_IdleTask(void)
{
    for(;;)
    {
        // idle loop
    }
}

static void Os_Dispatch(TaskType next)
{
    TaskType current = Os_RunningTask;
    CALL_POST_TASK_HOOK();
    printf("Dispatching from Task %d to Task %d\n", current, next);
    if (current != INVALID_TASK) {
        printf("Saved context of Task %d\n", current);
        Os_SaveContext(&Os_TaskTable[current].Context);
        printf("Current Task %d state: %d\n", current, Os_TaskTable[current].TaskState);
        if (Os_TaskTable[current].TaskState == RUNNING) {
            Os_TaskTable[current].TaskState = READY;
            printf("Task %d state changed to READY\n", current);
            ReadyQueuePush(current);
            OS_LOG("Task %d moved to READY", current);
        }
    }

    Os_RunningTask = next;
    ReadyQueueRemove(next);
    Os_TaskTable[next].TaskState = RUNNING;

    OS_LOG("Task %d is now RUNNING", next);
    CALL_PRE_TASK_HOOK();
    Os_RestoreContext(&Os_TaskTable[next].Context);
}

static void Os_Schedule(void)
{
    TaskType next = GetHighestReady();

    if (next != INVALID_TASK) {
        if (Os_RunningTask == INVALID_TASK) {
            OS_LOG("No task running, dispatching Task %d", next);
            Os_Dispatch(next);
        } else {
            Os_TaskControlBlockType* cur = &Os_TaskTable[Os_RunningTask];
            Os_TaskControlBlockType* nxt = &Os_TaskTable[next];

            if (nxt->CurrentPriority > cur->CurrentPriority &&
                cur->Preemption == PREEMPTIVE)
            {
                OS_LOG("Task %d preempted by Task %d", cur->TaskID, nxt->TaskID);
                Os_Dispatch(next);
            }
        }
    } else {
        if (Os_RunningTask == INVALID_TASK) {
            OS_LOG("No task is currently running");
            Os_IdleTask();
        }
    }
}

StatusType ActivateTask(TaskType TaskID)
{
    OS_LOG("ActivateTask: TaskID=%d", TaskID);
    if (TaskID >= NUMBER_OF_TASKS) {
        OS_LOG("ActivateTask failed: invalid ID %d", TaskID);
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_TaskControlBlockType* tcb = &Os_TaskTable[TaskID];

    if (tcb->TaskState == SUSPENDED) {
        tcb->TaskState = READY;
        tcb->QueuedActivations = 1;
        ReadyQueuePush(TaskID);
        OS_LOG("Task %d activated from SUSPENDED", TaskID);
    } else {
        if (tcb->QueuedActivations >= tcb->MaxActivations) {
            OS_LOG("Task %d activation limit reached", TaskID);
            CALL_ERROR_HOOK(E_OS_LIMIT);
            return E_OS_LIMIT;
        }
        tcb->QueuedActivations++;
        OS_LOG("Task %d queued activation, count=%d", TaskID, tcb->QueuedActivations);
    }

    Os_Schedule();
    return E_OK;
}

StatusType TerminateTask(void)
{
    OS_LOG("TerminateTask: TaskID=%d", Os_RunningTask);
    if (Os_RunningTask == INVALID_TASK) {
        OS_LOG("TerminateTask failed: no running task");
        CALL_ERROR_HOOK(E_OS_STATE);
        return E_OS_STATE;
    }

    Os_TaskControlBlockType* tcb = &Os_TaskTable[Os_RunningTask];

    if (tcb->QueuedActivations > 1) {
        tcb->QueuedActivations--;
        tcb->TaskState = READY;
        ReadyQueuePush(tcb->TaskID);
        OS_LOG("Task %d re-queued, remaining activations=%d", tcb->TaskID, tcb->QueuedActivations);
    } else {
        tcb->TaskState = SUSPENDED;
        tcb->QueuedActivations = 0;
        OS_LOG("Task %d terminated and moved to SUSPENDED", tcb->TaskID);
    }

    Os_RunningTask = INVALID_TASK;
    Os_Schedule();
    return E_OK;
}

StatusType ChainTask(TaskType TaskID)
{
    if (TaskID >= NUMBER_OF_TASKS) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }
    OS_LOG("ChainTask: Terminating current task and activating Task %d", TaskID);
    TerminateTask();
    ActivateTask(TaskID);

    return E_OK;
}

StatusType Schedule(void)
{
    Os_Schedule();
    return E_OK;
}

StatusType GetTaskID(TaskRefType TaskIDRef)
{
    if (NULL_PTR == TaskIDRef) {
        CALL_ERROR_HOOK(E_OS_PARAM_POINTER);
        return E_OS_PARAM_POINTER;
    }

    *TaskIDRef = Os_RunningTask;
    return E_OK;
}

StatusType GetTaskState(TaskType TaskID, TaskStateRefType StateRef)
{
    if (TaskID >= NUMBER_OF_TASKS) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }
    if (NULL_PTR == StateRef) {
        CALL_ERROR_HOOK(E_OS_PARAM_POINTER);
        return E_OS_PARAM_POINTER;
    }
    *StateRef = Os_TaskTable[TaskID].TaskState;
    return E_OK;
}

void Os_ActivateAutoStartTasks(void)
{
    for (uint8_t i = 0; i < NUMBER_OF_AUTOSTART_TASKS; i++) {
        ActivateTask(Os_AutoStartTasks[i]);
    }
}
