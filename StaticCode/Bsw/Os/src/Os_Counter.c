#include "Os_Counter.h"
#include "Os_Alarm.h"

Os_CounterType Counters[NUMBER_OF_COUNTERS] = {COUNTER_INIT};

Os_CounterType* GetCounter(CounterType id)
{
    if (id >= NUMBER_OF_COUNTERS) return NULL_PTR;
    return &Counters[id];
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

StatusType GetElapsedValue ( CounterType CounterID, TickRefType Value, TickRefType ElapsedValue )
{
    Os_CounterType* c;

    c = GetCounter(CounterID);
    *ElapsedValue = ( c->CurrentTick > *Value ) ? (c->CurrentTick - *Value) : ( c->MaxTick - *Value + c->CurrentTick );
    return E_OK;
}

StatusType IncrementCounter ( CounterType CounterID ) {
    Os_CounterType* c = GetCounter(CounterID);
    if (NULL_PTR == c) {
        return;
    }

    if (++c->CurrentTick > c->MaxTick) {
        c->CurrentTick = 0;
    }

    for (int i = 0; i < NUMBER_OF_ALARMS; i++) {
        Os_AlarmType* a = &Alarms[i];
        if (a->Active && a->CounterID == CounterID) {
            if (a->AlarmTime == c->CurrentTick) {
                if (a->ActionFunction) {
                    a->ActionFunction(a);
                }

                if (a->CycleTime > 0) {
                    // reschedule next tick
                    a->AlarmTime += a->CycleTime;
                } else {
                    // one-shot, deactivate
                    a->Active = FALSE;
                }
            }
        }
    }
}
