#include "Os_Queue.h"
#include "Os_Task.h"
#include "Os_Types.h"
#include "Os_Cfg.h"

ReadyQueueType ReadyQueue[MAX_PRIORITY];

bool ReadyQueueEmpty(ReadyQueueType* q) {
    return q->Head == q->Tail;
}

void ReadyQueueInit(ReadyQueueType* q) {
    q->Head = 0;
    q->Tail = 0;
}

void ReadyQueuePush(TaskType t) {
    ReadyQueueType* q = &ReadyQueue[Os_TaskTable[t].QueueIdx];
    q->Queue[q->Tail++] = t;
    if (q->Tail >= QUEUE_SIZE) {
        q->Tail = 0;
    }
}

TaskType ReadyQueueFront(ReadyQueueType* q) {
    return q->Queue[q->Head];
}

void ReadyQueueRemove(TaskType t) {
    ReadyQueueType* q = &ReadyQueue[Os_TaskTable[t].QueueIdx];
    uint8_t i = q->Head;
    while (i != q->Tail) {
        if (q->Queue[i] == t) {
            uint8_t j = i;
            while (j != q->Tail) {
                uint8_t next = (j + 1) % QUEUE_SIZE;
                q->Queue[j] = q->Queue[next];
                j = next;
            }
            if (q->Tail == 0) {
                q->Tail = QUEUE_SIZE - 1;
            } else {
                q->Tail--;
            }
            break;
        }
        i = (i + 1) % QUEUE_SIZE;
    }
}

TaskType GetHighestReady(void) {
    TaskType TaskID;
    for (uint8_t prio = 0; prio < MAX_PRIORITY; prio++) {
        if (!ReadyQueueEmpty(&ReadyQueue[prio])) {
            TaskID = ReadyQueueFront(&ReadyQueue[prio]);
            return TaskID;
        }
    }
    return INVALID_TASK;
}