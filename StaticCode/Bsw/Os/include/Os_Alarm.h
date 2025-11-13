#ifndef OS_ALARM_H
#define OS_ALARM_H

#include "Os_Types.h"

StatusType SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle);
StatusType SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle);
StatusType CancelAlarm(AlarmType AlarmID);
StatusType GetCounterValue(CounterType CounterID, TickType *Value);
StatusType GetCounterMax(CounterType CounterID, TickType *Value);
void Os_ActivateAutoStartAlarms(void);
void CounterTickHandler(CounterType CounterID);

#endif /* OS_ALARM_H */
