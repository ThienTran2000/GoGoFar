#ifndef __OS_COUNTER_H__
#define __OS_COUNTER_H__
#include "Os_Types.h"

StatusType GetCounterValue (CounterType CounterID, TickRefType Value );
StatusType GetElapsedValue ( CounterType CounterID, TickRefType Value, TickRefType ElapsedValue );
StatusType IncrementCounter ( CounterType CounterID );
StatusType GetCounterMax(CounterType CounterID, TickType *Value);
StatusType IncrementCounter ( CounterType CounterID );
#endif