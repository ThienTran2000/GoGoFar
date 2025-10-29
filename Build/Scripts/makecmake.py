import os
import sys

template = """
cmake_minimum_required(VERSION 3.9)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_TOOLCHAIN_FILE "{toolchain_file}")

project(GoGoFar C ASM)

include_directories(
    {include_dirs}
)

set(TARGET_NAME GoGoFar)
set(OUTPUT_FILE_NAME GoGoFar)
set(OUTPUT_DIR "../Output")

add_executable(${{TARGET_NAME}}
    {source_files}
)

set_target_properties(${{TARGET_NAME}} PROPERTIES
OUTPUT_NAME ${{OUTPUT_FILE_NAME}}
RUNTIME_OUTPUT_DIRECTORY ${{OUTPUT_DIR}}
)

set(CMAKE_EXECUTABLE_SUFFIX "${{OUTPUT_EXTENSION}}")
"""

input = [
    # add source directories here
    "../../Generated",
    "../../StaticCode",
]

banned = [
    # define banned paths or patterns here
]

def main(args):
    print(args)
    toolchain_file = "../toolchain_gcc.cmake"
    if len(args) > 0:
        if args[0] == "tricore":
            toolchain_file = "../toolchain_tricore.cmake"
        elif args[0] == "gcc":
            toolchain_file = "../toolchain_gcc.cmake"

    source = []
    include_dirs = set()

    for root_dir in input:
        for dirpath, dirnames, filenames in os.walk(root_dir):
            for filename in filenames:
                if filename.endswith(".cpp") or filename.endswith(".c") or filename.endswith(".s"):
                    filepath = os.path.join(dirpath, filename)
                    relpath = os.path.relpath(filepath, os.path.dirname(__file__))
                    if any(b in relpath for b in banned):
                        continue
                    source.append(relpath.replace("\\", "/"))
                if filename.endswith(".h") or filename.endswith(".hpp"):
                    print(filename)
                    filepath = os.path.join(dirpath, filename)
                    relpath = os.path.relpath(filepath, os.path.dirname(__file__))
                    if any(b in relpath for b in banned):
                        continue
                    include_dirs.add(os.path.relpath(dirpath, os.path.dirname(__file__)).replace("\\", "/"))
    
    with open("CmakeLists.txt", "w") as f:
        f.write(template.format(
            toolchain_file=toolchain_file,
            include_dirs="\n    ".join(sorted(include_dirs)),
            source_files="\n    ".join(sorted(source)),
        ))

if __name__ == "__main__":
    main(sys.argv[1:])
