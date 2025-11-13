#ifndef OS_QUEUE_H
#define OS_QUEUE_H

#include "Os_Types.h"
#include <stdbool.h>

extern Os_TaskControlBlockType Os_TaskTable[NUMBER_OF_TASKS];

bool ReadyQueueEmpty(ReadyQueueType* q);
void ReadyQueuePush(TaskType t);
TaskType ReadyQueueFront(ReadyQueueType* q);
void ReadyQueueRemove(TaskType t);
TaskType GetHighestReady(void);

#endif /* OS_QUEUE_H */
