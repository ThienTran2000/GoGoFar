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
set(CMAKE_C_FLAGS_INIT "-fno-common -fno-short-enums -O0 -g2 -W -Wall -Wextra -Wdiv-by-zero -Warray-bounds -Wcast-align -Wignored-qualifiers -Wformat -Wformat-security -pipe -DTRIBOARD_TC3X9_V2_0 -D__TC39XX__ -fshort-double -mtc162 -mversion-info")
set(CMAKE_ASM_FLAGS_INIT "-Wa,--gdwarf-2 -mtc162 -Wa,--insn32-preferred")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-mcpu=tc39xx -Wl,--gc-sections -mtc162 -Wl,--warn-orphan -Wl,-Map=../Output/${CMAKE_PROJECT_NAME}.map -Wl,--cref -fshort-double -Wl,-n -Wl,--extmap=a ")
# Optional: custom linker script
set(LINKER_SCRIPT "../Linker/Lcf_Gnuc_Tricore_Tc.lsl")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_INIT} -T${LINKER_SCRIPT}")

