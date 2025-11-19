#include "Os.h"
#include "Os_Types.h"

void ErrorHook(StatusType Error) {
    OS_LOG("ErrorHook: error id %d", Error);
}

void PreTaskHook(void) {

}

void PostTaskHook(void) {

}

void StartupHook(void) {

}

void ShutdownHook(StatusType Error) {
    OS_LOG("ShutdownHook: error id %d", Error);
}

ProtectionReturnType ProtectionHook(StatusType FatalError) {
    return PRO_SHUTDOWN;
}
