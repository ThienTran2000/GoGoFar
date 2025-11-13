#ifndef OS_EVENT_H
#define OS_EVENT_H

#include "Os_Types.h"

extern Os_TaskControlBlockType Os_TaskTable[NUMBER_OF_TASKS];
extern TaskType Os_RunningTask;

StatusType Os_SetEvent(TaskType TaskID, EventMaskType Mask);
StatusType ClearEvent(EventMaskType Mask);
StatusType GetEvent(TaskType TaskID, EventMaskType *Mask);
StatusType WaitEvent(EventMaskType Mask);

#endif /* OS_EVENT_H */
