#include "Os_Wrapper.h"
#include "Os_Task.h"
#include "Os_Event.h"

void Os_WrapperActivateTask(const Os_AlarmType *alarm) {
    OS_LOG("Alarm %d activating Task %d", alarm->AlarmID, alarm->ObjectId);
    ActivateTask(alarm->ObjectId);
    // Implementation
}

void Os_WrapperSetEvent(const Os_AlarmType *alarm) {
    OS_LOG("Alarm setting Event %d for Task %d", alarm->ObjectId, alarm->TaskID);
    Os_SetEvent(alarm->TaskID, alarm->ObjectId);
    // Implementation
}

void Os_WrapperCallout(const Os_AlarmType *alarm) {
    OS_LOG("Alarm %d callout", alarm->AlarmID);
}
