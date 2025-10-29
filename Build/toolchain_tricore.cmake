# ========================================
# Toolchain for TriCore (HighTec GCC)
# ========================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR tricore)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_C_STANDARD 99)
# Compiler root
set(COMPILER_ROOT "C:/HighTec/toolchains/tricore/v4.9.3.0-infineon-1.0")

# Compiler paths
set(CMAKE_C_COMPILER "${COMPILER_ROOT}/bin/tricore-gcc.exe")
set(CMAKE_ASM_COMPILER "${COMPILER_ROOT}/bin/tricore-gcc.exe")
set(CMAKE_AR "${COMPILER_ROOT}/bin/tricore-ar.exe")
set(CMAKE_OBJCOPY "${COMPILER_ROOT}/bin/tricore-objcopy.exe")
set(CMAKE_OBJDUMP "${COMPILER_ROOT}/bin/tricore-objdump.exe")
set(CMAKE_STRIP "${COMPILER_ROOT}/bin/tricore-strip.exe")
set(CMAKE_LINKER "${COMPILER_ROOT}/bin/tricore-ld.exe")

# Output file formats
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")

set(OUTPUT_EXTENSION ".elf")
# Flags
set(CMAKE_C_FLAGS_INIT "-mcpu=tc27xx -O2 -Wall -fmessage-length=0 -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS_INIT "-mcpu=tc27xx -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mcpu=tc27xx -Wl,--gc-sections -Wl,-Map=../Output/${CMAKE_PROJECT_NAME}.map")

# Optional: custom linker script
set(LINKER_SCRIPT "../Linker/linker_tc397.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_INIT} -T${LINKER_SCRIPT}")

