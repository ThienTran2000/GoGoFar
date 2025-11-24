#ifndef OS_ALARM_H
#define OS_ALARM_H

#include "Os_Types.h"

StatusType SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle);
StatusType SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle);
StatusType CancelAlarm(AlarmType AlarmID);

void Os_ActivateAutoStartAlarms(void);

extern Os_AlarmType Alarms[NUMBER_OF_ALARMS];

#endif /* OS_ALARM_H */
