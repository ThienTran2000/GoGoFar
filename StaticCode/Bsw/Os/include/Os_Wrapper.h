#ifndef OS_WRAPPER_H
#define OS_WRAPPER_H

#include "Os_Types.h"

void Os_WrapperActivateTask(const Os_AlarmType *alarm);
void Os_WrapperSetEvent(const Os_AlarmType *alarm);
void Os_WrapperCallout(const Os_AlarmType *alarm);

#endif /* OS_WRAPPER_H */
