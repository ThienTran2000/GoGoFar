#include "Os_Alarm.h"
#include "Os_Cfg.h"
#include "Os_Wrapper.h"

Os_AlarmType Alarms[NUMBER_OF_ALARMS] = {ALARM_INIT};

AlarmType AlarmAutoStart[NUMBER_OF_ALARM_AUTOSTARTS] = {ALARM_AUTOSTART};

static Os_AlarmType* GetAlarm(AlarmType id) {
    if (id >= NUMBER_OF_ALARMS) return NULL_PTR;
    return &Alarms[id];
}

StatusType SetRelAlarm(AlarmType AlarmID, TickType Increment, TickType Cycle) {
    Os_AlarmType* a = GetAlarm(AlarmID);
    if (NULL_PTR == a) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }
    if (a->Active) {
        CALL_ERROR_HOOK(E_OS_STATE);
        return E_OS_STATE;
    }

    Os_CounterType* c = GetCounter(a->CounterID);
    if (NULL_PTR == c) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    a->AlarmTime = c->CurrentTick + Increment;
    a->CycleTime = Cycle;
    a->Active = TRUE;

    return E_OK;
}

StatusType SetAbsAlarm(AlarmType AlarmID, TickType Start, TickType Cycle) {
    Os_AlarmType* a = GetAlarm(AlarmID);
    if (NULL_PTR == a) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }
    if (a->Active) {
        CALL_ERROR_HOOK(E_OS_STATE);
        return E_OS_STATE;
    }

    a->AlarmTime = Start;
    a->CycleTime = Cycle;
    a->Active = TRUE;

    return E_OK;
}

StatusType CancelAlarm(AlarmType AlarmID) {
    Os_AlarmType* a = GetAlarm(AlarmID);
    if (NULL_PTR == a) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }
    if (!a->Active) {
        CALL_ERROR_HOOK(E_OS_NOFUNC);
        return E_OS_NOFUNC;
    }

    a->Active = FALSE;
    a->CycleTime = 0;

    return E_OK;
}


void Os_ActivateAutoStartAlarms(void)
{
    for (uint8 i = 0; i < NUMBER_OF_ALARM_AUTOSTARTS; i++) {
        SetRelAlarm(AlarmAutoStart[i], Alarms[AlarmAutoStart[i]].AlarmTime, Alarms[AlarmAutoStart[i]].CycleTime);
    }
}
