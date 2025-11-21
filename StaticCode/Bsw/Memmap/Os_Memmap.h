
#if 0

#elif OS_START_SEC_VAR_INIT_8
    #undef OS_START_SEC_VAR_INIT_8
    #pragma section ".data_8_core0" aw 1
#elif OS_STOP_SEC_VAR_INIT_8
    #undef OS_STOP_SEC_VAR_INIT_8
    #pragma section
#elif OS_START_SEC_VAR_CLEARED_8
    #undef OS_START_SEC_VAR_CLEARED_8
    #pragma section ".bss_8_core0" aw 1
#elif OS_STOP_SEC_VAR_CLEARED_8
    #undef OS_STOP_SEC_VAR_CLEARED_8
    #pragma section
#elif OS_START_SEC_VAR_POWER_ON_CLEARED_8
    #undef OS_START_SEC_VAR_POWER_ON_CLEARED_8
    #pragma section ".bss_8_core0" aw 1
#elif OS_STOP_SEC_VAR_POWER_ON_CLEARED_8
    #undef OS_STOP_SEC_VAR_POWER_ON_CLEARED_8
    #pragma section
#elif OS_START_SEC_CONST_8
    #undef OS_START_SEC_CONST_8
    #pragma section ".rodata_8_core0" aw 1
#elif OS_STOP_SEC_CONST_8
    #undef OS_STOP_SEC_CONST_8
    #pragma section
#elif OS_START_SEC_CONFIG_DATA_8
    #undef OS_START_SEC_CONFIG_DATA_8
    #undef OS_START_SEC_CONST_8
    #pragma section ".rodata_8_core0" aw 1
#elif OS_STOP_SEC_CONFIG_DATA_8
    #undef OS_STOP_SEC_CONFIG_DATA_8
    #pragma section
#elif OS_START_SEC_CODE_8
    #undef OS_START_SEC_CODE_8
    #pragma section ".text_8_core0" aw 1
#elif OS_STOP_SEC_CODE_8
    #undef OS_STOP_SEC_CODE_8
    #pragma section
#elif OS_START_SEC_VAR_INIT_16
    #undef OS_START_SEC_VAR_INIT_16
    #pragma section ".data_16_core0" aw 1
#elif OS_STOP_SEC_VAR_INIT_16
    #undef OS_STOP_SEC_VAR_INIT_16
    #pragma section
#elif OS_START_SEC_VAR_CLEARED_16
    #undef OS_START_SEC_VAR_CLEARED_16
    #pragma section ".bss_16_core0" aw 1
#elif OS_STOP_SEC_VAR_CLEARED_16
    #undef OS_STOP_SEC_VAR_CLEARED_16
    #pragma section
#elif OS_START_SEC_VAR_POWER_ON_CLEARED_16
    #undef OS_START_SEC_VAR_POWER_ON_CLEARED_16
    #pragma section ".bss_16_core0" aw 1
#elif OS_STOP_SEC_VAR_POWER_ON_CLEARED_16
    #undef OS_STOP_SEC_VAR_POWER_ON_CLEARED_16
    #pragma section
#elif OS_START_SEC_CONST_16
    #undef OS_START_SEC_CONST_16
    #pragma section ".rodata_16_core0" aw 1
#elif OS_STOP_SEC_CONST_16
    #undef OS_STOP_SEC_CONST_16
    #pragma section
#elif OS_START_SEC_CONFIG_DATA_16
    #undef OS_START_SEC_CONFIG_DATA_16
    #undef OS_START_SEC_CONST_16
    #pragma section ".rodata_16_core0" aw 1
#elif OS_STOP_SEC_CONFIG_DATA_16
    #undef OS_STOP_SEC_CONFIG_DATA_16
    #pragma section
#elif OS_START_SEC_CODE_16
    #undef OS_START_SEC_CODE_16
    #pragma section ".text_16_core0" aw 1
#elif OS_STOP_SEC_CODE_16
    #undef OS_STOP_SEC_CODE_16
    #pragma section
#elif OS_START_SEC_VAR_INIT_32
    #undef OS_START_SEC_VAR_INIT_32
    #pragma section ".data_32_core0" aw 1
#elif OS_STOP_SEC_VAR_INIT_32
    #undef OS_STOP_SEC_VAR_INIT_32
    #pragma section
#elif OS_START_SEC_VAR_CLEARED_32
    #undef OS_START_SEC_VAR_CLEARED_32
    #pragma section ".bss_32_core0" aw 1
#elif OS_STOP_SEC_VAR_CLEARED_32
    #undef OS_STOP_SEC_VAR_CLEARED_32
    #pragma section
#elif OS_START_SEC_VAR_POWER_ON_CLEARED_32
    #undef OS_START_SEC_VAR_POWER_ON_CLEARED_32
    #pragma section ".bss_32_core0" aw 1
#elif OS_STOP_SEC_VAR_POWER_ON_CLEARED_32
    #undef OS_STOP_SEC_VAR_POWER_ON_CLEARED_32
    #pragma section
#elif OS_START_SEC_CONST_32
    #undef OS_START_SEC_CONST_32
    #pragma section ".rodata_32_core0" aw 1
#elif OS_STOP_SEC_CONST_32
    #undef OS_STOP_SEC_CONST_32
    #pragma section
#elif OS_START_SEC_CONFIG_DATA_32
    #undef OS_START_SEC_CONFIG_DATA_32
    #undef OS_START_SEC_CONST_32
    #pragma section ".rodata_32_core0" aw 1
#elif OS_STOP_SEC_CONFIG_DATA_32
    #undef OS_STOP_SEC_CONFIG_DATA_32
    #pragma section
#elif OS_START_SEC_CODE_32
    #undef OS_START_SEC_CODE_32
    #pragma section ".text_32_core0" aw 1
#elif OS_STOP_SEC_CODE_32
    #undef OS_STOP_SEC_CODE_32
    #pragma section
#elif OS_START_SEC_VAR_INIT_UNSPECIFIED
    #undef OS_START_SEC_VAR_INIT_UNSPECIFIED
    #pragma section ".data_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef OS_STOP_SEC_VAR_INIT_UNSPECIFIED
    #pragma section
#elif OS_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef OS_START_SEC_VAR_CLEARED_UNSPECIFIED
    #pragma section ".bss_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #pragma section
#elif OS_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #undef OS_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #pragma section ".bss_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #undef OS_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #pragma section
#elif OS_START_SEC_CONST_UNSPECIFIED
    #undef OS_START_SEC_CONST_UNSPECIFIED
    #pragma section ".rodata_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_CONST_UNSPECIFIED
    #undef OS_STOP_SEC_CONST_UNSPECIFIED
    #pragma section
#elif OS_START_SEC_CONFIG_DATA_UNSPECIFIED
    #undef OS_START_SEC_CONFIG_DATA_UNSPECIFIED
    #undef OS_START_SEC_CONST_UNSPECIFIED
    #pragma section ".rodata_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #undef OS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #pragma section
#elif OS_START_SEC_CODE_UNSPECIFIED
    #undef OS_START_SEC_CODE_UNSPECIFIED
    #pragma section ".text_UNSPECIFIED_core0" aw 1
#elif OS_STOP_SEC_CODE_UNSPECIFIED
    #undef OS_STOP_SEC_CODE_UNSPECIFIED
    #pragma section

    #error "included section is undefine in Os_Memmap"
#endif