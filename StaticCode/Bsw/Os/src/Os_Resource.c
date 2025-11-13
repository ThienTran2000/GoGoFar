#include "Os_Resource.h"
#include "Os_Types.h"
#include "Os_Cfg.h"

Os_ResourceType Resources[NUMBER_OF_RESOURCES] = {RESOURCE_INIT};

StatusType GetResource(ResourceType ResID) {
    if (ResID >= NUMBER_OF_RESOURCES) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_ResourceType* r = &Resources[ResID];
    Os_TaskControlBlockType* t = &Os_TaskTable[Os_RunningTask];

    if (r->OwnerTask == t->TaskID) {
        r->Nesting++;
        return E_OK;
    }

    r->OwnerTask = t->TaskID;
    r->Nesting = 1;

    if (t->CurrentPriority < r->CeilingPriority) {
        t->CurrentPriority = r->CeilingPriority;
    }

    return E_OK;
}

StatusType ReleaseResource(ResourceType ResID) {
    if (ResID >= NUMBER_OF_RESOURCES) {
        CALL_ERROR_HOOK(E_OS_ID);
        return E_OS_ID;
    }

    Os_ResourceType* r = &Resources[ResID];
    Os_TaskControlBlockType* t = &Os_TaskTable[Os_RunningTask];

    if (r->OwnerTask != t->TaskID) {
        CALL_ERROR_HOOK(E_OS_NOFUNC);
        return E_OS_NOFUNC;
    }

    if (--r->Nesting == 0) {
        r->OwnerTask = NO_OWNER;
        t->CurrentPriority = t->BasePriority;
    }

    return E_OK;
}
