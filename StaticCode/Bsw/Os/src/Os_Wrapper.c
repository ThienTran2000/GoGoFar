#include "Os_Wrapper.h"
#include "Os_Task.h"
#include "Os_Event.h"

void Os_WrapperActivateTask(const Os_AlarmType *alarm) {
    OS_LOG("Alarm %d activating Task %d", alarm->AlarmID, alarm->ObjectId);
    ActivateTask(alarm->ObjectId);
    // Implementation
}

void Os_WrapperSetEvent(const Os_AlarmType *alarm) {
    OS_LOG("Alarm %d setting Event %d", alarm->AlarmID, alarm->ObjectId);
    // Implementation
}

void Os_WrapperCallout(const Os_AlarmType *alarm) {
    OS_LOG("Alarm %d calling out Task %d", alarm->AlarmID, alarm->ObjectId);
}
