#ifndef OS_CFG_H
#define OS_CFG_H
#include "Os_Types.h"

#define MAX_PRIORITY                    2
#define QUEUE_SIZE                      2
#define NO_OWNER                        NUMBER_OF_TASKS

/*=================================================================*/
/*                      Hook Function Configuration                */
/*=================================================================*/
#define USEERRORHOOK

#define USEPROTECTIONHOOK

#define USESTARTUPHOOK

#define USEPRETASKHOOK

#define USEPOSTTASKHOOK

#define USESHUTDOWNHOOK

/*=================================================================*/
/*                  Application Mode Configuration                */
/*=================================================================*/
#define OSDEFAULTAPPMODE                0

/*=================================================================*/
/*                      Alarm Configuration                        */
/*=================================================================*/
#define NUMBER_OF_ALARMS                3
#define NUMBER_OF_ALARM_AUTOSTARTS      3
#define NUMBER_OF_ALARMS_CALLBACKS      1
#define AlarmTimingTask10ms             0
#define AlarmEvent20ms                  1
#define AlarmCallout100ms               2

#define ALARM_INIT                                                  \
    { /* AlarmTimingTask10ms */                                     \
        /* Alarm ID */                  0,                          \
        /* Counter ID */                0,                          \
        /* Alarm Time */                500,                        \
        /* Cycle Time */                10,                         \
        /* Action Function */           &Os_WrapperActivateTask,    \
        /* Object ID */                 0,                          \
        /* Task ID */                   0,                          \
        /* Active */                    false                       \
    },                                                              \
    { /* AlarmEvent20ms */                                          \
        /* Alarm ID */                  1,                          \
        /* Counter ID */                0,                          \
        /* Alarm Time */                100,                        \
        /* Cycle Time */                20,                         \
        /* Action Function */           &Os_WrapperSetEvent,        \
        /* Object ID */                 1,                          \
        /* Task ID */                   1,                          \
        /* Active */                    false                       \
    },                                                              \
    { /* AlarmCallout100ms */                                       \
        /* Alarm ID */                  2,                          \
        /* Counter ID */                0,                          \
        /* Alarm Time */                100,                        \
        /* Cycle Time */                100,                        \
        /* Action Function */           &Os_WrapperCallout,         \
        /* Object ID */                 0,                          \
        /* Task ID */                   0,                          \
        /* Active */                    false                       \
    }

#define ALARM_AUTOSTART                                             \
        AlarmTimingTask10ms,                                        \
        AlarmEvent20ms,                                             \
        AlarmCallout100ms                                           \

/*=================================================================*/
/*                      Counter Configuration                      */
/*=================================================================*/
#define NUMBER_OF_COUNTERS              1
#define CounterHardwareTimer            0

#define COUNTER_INIT                                                \
    { /* HardwareCounter */                                         \
        /* Counter ID */                0,                          \
        /* CurrentTick */               0,                          \
        /* MaxTick */                   4294967295                  \
    }

/*=================================================================*/
/*                      Resource Configuration                     */
/*=================================================================*/
#define NUMBER_OF_RESOURCES             1
#define Resource0                       0

#define RESOURCE_INIT                                               \
    { /* Resource 0 */                                              \
        /* Resource ID */               0,                          \
        /* Ceiling Priority */          0,                          \
        /* Owner Task */                NO_OWNER,                   \
        /* Nesting */                   0                           \
    }

/*=================================================================*/
/*                      Task Configuration                         */
/*=================================================================*/
#define NUMBER_OF_TASKS                 3

#define Os_TaskInit                     0
#define Os_TaskTiming10ms               1
#define Os_TaskEvent20ms                2
extern void Os_TaskInit_Entry(void);
extern void Os_TaskTiming10ms_Entry(void);
extern void Os_TaskEvent20ms_Entry(void);

#define NUMBER_OF_AUTOSTART_TASKS       2
#define TASK_AUTOSTART                                              \
        Os_TaskInit,                                                \
        Os_TaskEvent20ms                                            \

#define TASK_INIT                                                   \
    { /* Os_TaskInit */                                             \
        /* Context */                   {0, 0},                     \
        /* Event Mask */                0,                          \
        /* Wait Mask */                 0,                          \
        /* Entry */                     &Os_TaskInit_Entry,         \
        /* Stack Size */                1024,                       \
        /* Task ID */                   0,                          \
        /* Task State */                SUSPENDED,                  \
        /* Current Priority */          100,                        \
        /* Base Priority */             100,                        \
        /* Max Activations */           1,                          \
        /* Queued Activations */        0,                          \
        /* Task Type */                 TASK_BASIC,                 \
        /* Preemption */                NON_PREEMPTIVE,             \
        /* Queue Index */               0                           \
    },                                                              \
    { /* Os_TaskTiming10ms */                                       \
        /* Context */                   {0, 0},                     \
        /* Event Mask */                0,                          \
        /* Wait Mask */                 0,                          \
        /* Entry */                     &Os_TaskTiming10ms_Entry,   \
        /* Stack Size */                1024,                       \
        /* Task ID */                   1,                          \
        /* Task State */                SUSPENDED,                  \
        /* Current Priority */          50,                         \
        /* Base Priority */             50,                         \
        /* Max Activations */           1,                          \
        /* Queued Activations */        0,                          \
        /* Task Type */                 TASK_BASIC,                 \
        /* Preemption */                PREEMPTIVE,                 \
        /* Queue Index */               1                           \
    },                                                              \
    { /* Os_TaskEvent20ms */                                        \
        /* Context */                   {0, 0},                     \
        /* Event Mask */                0,                          \
        /* Wait Mask */                 0,                          \
        /* Entry */                     &Os_TaskEvent20ms_Entry,    \
        /* Stack Size */                512,                        \
        /* Task ID */                   2,                          \
        /* Task State */                SUSPENDED,                  \
        /* Current Priority */          50,                         \
        /* Base Priority */             50,                         \
        /* Max Activations */           1,                          \
        /* Queued Activations */        0,                          \
        /* Task Type */                 TASK_EXTENDED,              \
        /* Preemption */                PREEMPTIVE,                 \
        /* Queue Index */               1                           \
    }

/*=================================================================*/
/*                      Event Configuration                        */
/*=================================================================*/
#define NUMBER_OF_EVENTS               1
#define Os_Event20ms                   1
#define EVENT_INIT                                                  \
    { /* Os_TaskEvent20ms */                                        \
        /* Event Mask */               0x00000001                   \
    }

#endif /* OS_CFG_H */
