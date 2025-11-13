# ========================================
# Toolchain for GCC (Windows / MinGW)
# ========================================

# Hệ điều hành và kiến trúc
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Compiler paths
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_ASSEMBLER_COMPILER "C:/MinGW/bin/gcc.exe")

# Flags mặc định cho GCC
set(CMAKE_C_FLAGS_INIT "-Wall -O0 -g")
set(CMAKE_ASM_FLAGS_INIT "-Wall -O0 -g")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")

# In thông tin compiler
set(OUTPUT_EXTENSION ".exe")

