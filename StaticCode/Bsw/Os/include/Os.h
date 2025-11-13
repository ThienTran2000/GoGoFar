#ifndef OS_H
#define OS_H

#include "Os_Types.h"
#include "Os_Cfg.h"
#include "Os_Task.h"
#include "Os_Alarm.h"
#include "Os_Event.h"
#include "Os_Resource.h"
#include "Os_Queue.h"

StatusType GetActiveApplicationMode(AppModeType *Mode);
StatusType StartOS(AppModeType mode);

#endif /* OS_H */
