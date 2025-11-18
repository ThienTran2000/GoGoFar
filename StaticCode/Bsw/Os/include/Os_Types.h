#ifndef OS_TYPES_H
#define OS_TYPES_H

#include "Os_Porting.h"
#include "Os_Cfg.h"

#define LOG_ENABLE

#ifdef LOG_ENABLE
#include <stdio.h>
#define OS_LOG(fmt, ...)
#else
#define OS_LOG(fmt, ...)
#endif

#define INVALID_TASK        ((TaskType)0xFF)

/* Status type for all services */
typedef uint8             StatusType;

/* Task ID type */
typedef uint8             TaskType;

/* Event mask type */
typedef uint32            EventMaskType;

/* Resource ID type */
typedef uint8             ResourceType;

/* Counter ID type */
typedef uint8             CounterType;

/* Alarm ID type */
typedef uint8             AlarmType;

/* Tick type */
typedef uint32            TickType;

/* Tick type reference  */
typedef TickType*         TickRefType;

/* Application mode type */
typedef uint8             AppModeType;

/* Task state type */
typedef uint8             TaskStateType;
#define SUSPENDED          ((TaskStateType)0x00)
#define READY              ((TaskStateType)0x01)
#define RUNNING            ((TaskStateType)0x02)
#define WAITING            ((TaskStateType)0x03)

/* Common return values */
#define E_OK                0x00
#define E_OS_ACCESS         0x01
#define E_OS_ID             0x02
#define E_OS_STATE          0x03
#define E_OS_NOFUNC         0x04
#define E_OS_LIMIT          0x05
#define E_OS_PARAM_POINTER  0x06

/* Task type */
typedef uint8               Os_TaskTypeType;
#define TASK_BASIC          ((Os_TaskTypeType)0x00)
#define TASK_EXTENDED       ((Os_TaskTypeType)0x01)

/* Task preemption */
typedef uint8               Os_TaskPreemptionType;
#define NON_PREEMPTIVE      ((Os_TaskPreemptionType)0x00)
#define PREEMPTIVE          ((Os_TaskPreemptionType)0x01)

typedef void (*Os_EntryType)(void);

typedef struct {
    Os_TaskContextType      Context;
    EventMaskType           EventMask;
    EventMaskType           WaitMask;
    Os_EntryType            Entry;
    uint16                  StackSize;
    TaskType                TaskID;
    TaskStateType           TaskState;
    uint8                   CurrentPriority;
    uint8                   BasePriority;
    uint8                   MaxActivations;
    uint8                   QueuedActivations;
    Os_TaskTypeType         TaskType;
    Os_TaskPreemptionType   Preemption;
    uint8                   QueueIdx;
} Os_TaskControlBlockType;

typedef uint8             Os_AlarmObjectIdType;
typedef struct Os_AlarmType_t Os_AlarmType;
typedef void (*Os_AlarmActionType)(const Os_AlarmType *);

struct Os_AlarmType_t {
    AlarmType               AlarmID;
    CounterType             CounterID;
    TickType                AlarmTime;
    TickType                CycleTime;
    Os_AlarmActionType      ActionFunction;
    Os_AlarmObjectIdType    ObjectId;
    TaskType                TaskID;
    boolean                    Active;
} ;


/* Reference types */
typedef TaskType*           TaskRefType;
typedef TaskStateType*      TaskStateRefType;
typedef EventMaskType*      EventMaskRefType;

typedef struct {
    TaskType                Queue[QUEUE_SIZE];
    uint8                 Head;
    uint8                 Tail;
} ReadyQueueType;

typedef struct {
    CounterType             CounterID;
    TickType                CurrentTick;
    TickType                MaxTick;
} Os_CounterType;

typedef struct {
    ResourceType            ResourceID;
    uint8                 CeilingPriority;
    TaskType                OwnerTask;
    uint8                 Nesting;
} Os_ResourceType;

typedef uint8             ProtectionReturnType;
#define PRO_SHUTDOWN        ((ProtectionReturnType)0x00)
#define PRO_TERMINATE       ((ProtectionReturnType)0x01)

#ifdef USEERRORHOOK
#define ERROR_HOOK_FUNCTION             ErrorHook
extern void ErrorHook(StatusType Error);
#define CALL_ERROR_HOOK(err) ERROR_HOOK_FUNCTION(err)
#else
#define CALL_ERROR_HOOK(err)
#endif

#ifdef USEPRETASKHOOK
#define PRE_TASK_HOOK_FUNCTION          PreTaskHook
extern void PreTaskHook(void);
#define CALL_PRE_TASK_HOOK() PRE_TASK_HOOK_FUNCTION()
#else
#define CALL_PRE_TASK_HOOK()
#endif

#ifdef USEPOSTTASKHOOK
#define POST_TASK_HOOK_FUNCTION         PostTaskHook
extern void PostTaskHook(void);
#define CALL_POST_TASK_HOOK() POST_TASK_HOOK_FUNCTION()
#else
#define CALL_POST_TASK_HOOK()
#endif

#ifdef USESTARTUPHOOK
#define STARTUP_HOOK_FUNCTION           StartupHook
extern void StartupHook(void);
#define CALL_STARTUP_HOOK() STARTUP_HOOK_FUNCTION()
#else
#define CALL_STARTUP_HOOK()
#endif

#ifdef USESHUTDOWNHOOK
#define SHUTDOWN_HOOK_FUNCTION          ShutdownHook
extern void ShutdownHook(StatusType Error);
#define CALL_SHUTDOWN_HOOK(err) SHUTDOWN_HOOK_FUNCTION(err)
#else
#define CALL_SHUTDOWN_HOOK(err)
#endif

#ifdef USEPROTECTIONHOOK
#define PROTECTION_HOOK_FUNCTION        ProtectionHook
extern ProtectionReturnType ProtectionHook(StatusType FatalError);
#define CALL_PROTECTION_HOOK(err) PROTECTION_HOOK_FUNCTION(err)
#else
#define CALL_PROTECTION_HOOK(err)
#endif

#endif /* OS_TYPES_H */

