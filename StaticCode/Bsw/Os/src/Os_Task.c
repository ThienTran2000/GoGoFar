#include "Os_Task.h"
#include "Os_Queue.h"
#include "Os_Types.h"
#include "Os_Cfg.h"
#include <stdio.h>

Os_TaskControlBlockType Os_TaskTable[NUMBER_OF_TASKS] = {TASK_INIT};
TaskType Os_AutoStartTasks[NUMBER_OF_AUTOSTART_TASKS] = {TASK_AUTOSTART};
TaskType Os_RunningTask = INVALID_TASK;
volatile int Os_ISR_Level = 0;
volatile bool Os_DeferredSchedule = false;
Os_TaskContextType Os_IdleTaskContext = {0, 0};

void Os_CreateContext(Os_TaskContextType* ctx)
{
    OS_LOG("Create context");
    ctx->Os_StackPointer = 1;
    ctx->Os_MSPStackPointer = 1;
}

void Os_SaveContext(Os_TaskContextType* ctx)
{
    ctx->Os_StackPointer = 0;
    ctx->Os_MSPStackPointer = 0;
}

void Os_RestoreContext(Os_TaskContextType* ctx)
{
    Os_TaskTable[Os_RunningTask].Entry();
}

static void Os_Dispatch(TaskType next)
{
    TaskType current = Os_RunningTask;
    CALL_POST_TASK_HOOK();
    if (current != INVALID_TASK) {
        Os_SaveContext(&Os_TaskTable[current].Context);
        if (Os_TaskTable[current].TaskState == RUNNING) {
            Os_TaskTable[current].TaskState = READY;
            ReadyQueuePush(current);
            OS_LOG("Task %d moved to READY", current);
        }
    } else {
        /* Should save context of idle task before switch to other task */
        Os_SaveContext(&Os_IdleTaskContext);
    }

    Os_RunningTask = next;
    ReadyQueueRemove(next);
    Os_TaskTable[next].TaskState = RUNNING;

    OS_LOG("Task %d is now RUNNING", next);
    CALL_PRE_TASK_HOOK();
    Os_RestoreContext(&Os_TaskTable[next].Context);
}

void Os_Schedule(void)
{
    Os_DeferredSchedule = false;
    TaskType next = GetHighestReady();
    OS_LOG("Call scheduler");
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
            Os_RestoreContext(&Os_IdleTaskContext);
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
        /* Os should create context of task if change state from SUSPENDED to READY */
        Os_CreateContext(&(tcb->Context));
    } else {
        if (tcb->QueuedActivations >= tcb->MaxActivations) {
            OS_LOG("Task %d activation limit reached", TaskID);
            CALL_ERROR_HOOK(E_OS_LIMIT);
            return E_OS_LIMIT;
        }
        tcb->QueuedActivations++;
        OS_LOG("Task %d queued activation, count=%d", TaskID, tcb->QueuedActivations);
    }

    if (Os_ISR_Level > 0) {
        Os_DeferredSchedule = true;
    } else {
        Os_Schedule();
    }
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

    if (TaskID >= NUMBER_OF_TASKS) {
        OS_LOG("ActivateTask failed: invalid ID %d", TaskID);
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    tcb = &Os_TaskTable[TaskID];

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
    TaskType TaskID;
    for (uint8_t i = 0; i < NUMBER_OF_AUTOSTART_TASKS; i++) {
        TaskID = Os_AutoStartTasks[i];

        Os_TaskControlBlockType* tcb = &Os_TaskTable[TaskID];

        tcb->TaskState = READY;
        tcb->QueuedActivations = 1;
        ReadyQueuePush(TaskID);
        OS_LOG("Auto start Task: TaskID=%d", TaskID);
        Os_CreateContext(&(tcb->Context));
        /* Os should create context of task if change state from SUSPENDED to READY */
    }
    /* Create context of Idle Task here */
    Os_CreateContext(&Os_IdleTaskContext);
}
