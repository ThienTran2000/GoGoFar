#include "EcuM.h"
#include "Os.h"

#define ECUM_START_SLAVE_CORE_1 TRUE
void _START1(void);


void EcuM_Init(void)
{
#if TRUE == ECUM_START_SLAVE_CORE_1
    OsStartSlaveCore(1, (uint32)_START1);
#endif
    /* EcuM should be defined in future */
    StartOS(OSDEFAULTAPPMODE);
}