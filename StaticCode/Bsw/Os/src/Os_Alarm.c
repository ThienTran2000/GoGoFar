#include "Os_Alarm.h"
#include "Os_Cfg.h"
#include "Os_Wrapper.h"
#include "Os_Task.h"

Os_AlarmType Alarms[NUMBER_OF_ALARMS] = {ALARM_INIT};
Os_CounterType Counters[NUMBER_OF_COUNTERS] = {COUNTER_INIT};
AlarmType AlarmAutoStart[NUMBER_OF_ALARM_AUTOSTARTS] = {ALARM_AUTOSTART};
extern volatile int Os_ISR_Level;
extern volatile bool Os_DeferredSchedule;

static Os_AlarmType* GetAlarm(AlarmType id) {
    if (id >= NUMBER_OF_ALARMS) return NULL_PTR;
    return &Alarms[id];
}

static Os_CounterType* GetCounter(CounterType id) {
    if (id >= NUMBER_OF_COUNTERS) return NULL_PTR;
    return &Counters[id];
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
    a->Active = true;

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
    a->Active = true;

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

    a->Active = false;
    a->CycleTime = 0;

    return E_OK;
}

StatusType GetCounterValue(CounterType CounterID, TickType *Value) {
    if (NULL_PTR == Value) {
        CALL_ERROR_HOOK(E_OS_PARAM_POINTER);
        return E_OS_PARAM_POINTER;
    }

    Os_CounterType* c = GetCounter(CounterID);
    if (NULL_PTR == c) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    *Value = c->CurrentTick;
    return E_OK;
}

StatusType GetCounterMax(CounterType CounterID, TickType *Value) {
    if (NULL_PTR == Value) {
        CALL_ERROR_HOOK(E_OS_PARAM_POINTER);
        return E_OS_PARAM_POINTER;
    }

    Os_CounterType* c = GetCounter(CounterID);
    if (NULL_PTR == c) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    *Value = c->MaxTick;
    return E_OK;
}

void CounterTickHandler(CounterType CounterID) {
    ENTER_ISR2();
    Os_CounterType* c = GetCounter(CounterID);
    if (c == NULL_PTR) {
        return;
    }

    /* update hardware counter with wrap */
    c->CurrentTick++;
    if (c->CurrentTick > c->MaxTick) {
        c->CurrentTick = 0;
    }
    for (int i = 0; i < NUMBER_OF_ALARMS; i++) {
        Os_AlarmType* a = &Alarms[i];

        if (!a->Active || a->CounterID != CounterID)
            continue;

        /* Check if alarm should fire */
        if (a->AlarmTime == c->CurrentTick) {

            /* Action */
            if (a->ActionFunction) {
                a->ActionFunction(a);
            }

            if (a->CycleTime > 0) {
                /* reschedule with wrap-around */
                a->AlarmTime += a->CycleTime;
                if (a->AlarmTime > c->MaxTick) {
                    a->AlarmTime %= (c->MaxTick + 1);
                }
            } else {
                /* one-shot */
                a->Active = false;
            }
        }
    }
    EXIT_ISR2();
}

void Os_ActivateAutoStartAlarms(void)
{
    for (uint8_t i = 0; i < NUMBER_OF_ALARM_AUTOSTARTS; i++) {
        SetRelAlarm(AlarmAutoStart[i], Alarms[AlarmAutoStart[i]].AlarmTime, Alarms[AlarmAutoStart[i]].CycleTime);
    }
}
