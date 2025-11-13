#ifndef OS_RESOURCE_H
#define OS_RESOURCE_H

#include "Os_Types.h"

extern Os_TaskControlBlockType Os_TaskTable[NUMBER_OF_TASKS];
extern TaskType Os_RunningTask;

StatusType GetResource(ResourceType ResID);
StatusType ReleaseResource(ResourceType ResID);

#endif /* OS_RESOURCE_H */
