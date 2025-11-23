#ifndef OS_TASK_H
#define OS_TASK_H

#include "Os_Types.h"

StatusType ActivateTask(TaskType TaskID);
StatusType TerminateTask(void);
StatusType ChainTask(TaskType TaskID);
StatusType Schedule(void);
StatusType GetTaskID(TaskType *TaskID);
StatusType GetTaskState(TaskType TaskID, TaskStateType *StateRef);
void Os_Schedule(void);
void Os_ActivateAutoStartTasks(void);
void Os_RestoreContext(Os_TaskContextType *ctx);

#endif /* OS_TASK_H */
