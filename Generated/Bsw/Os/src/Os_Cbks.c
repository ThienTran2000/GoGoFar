#include "Os.h"
#include "Os_Types.h"

void ErrorHook(StatusType Error) {

}

void PreTaskHook(void) {

}

void PostTaskHook(void) {

}

void StartupHook(void) {

}

void ShutdownHook(StatusType Error) {

}

ProtectionReturnType ProtectionHook(StatusType FatalError) {
    return PRO_SHUTDOWN;
}
