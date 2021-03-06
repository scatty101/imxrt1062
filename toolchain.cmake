# We are cross compileing
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# We use bare metal
set(TOOLCHAIN_PREFIX arm-none-eabi-)
set(TOOLCHAIN_POSTFIX .exe)

# Cmd for win cmd, can be added unix
set(SEARCH_CMD where)

# Find toolchain
execute_process(
    COMMAND ${SEARCH_CMD} ${TOOLCHAIN_PREFIX}gcc
    OUTPUT_VARIABLE TOOLCHAIN_PATH 
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get directory
get_filename_component(ARM_TOOLCHAIN_PATH ${TOOLCHAIN_PATH} DIRECTORY)
# Try to compile static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Set compilers
set(CMAKE_ASM_COMPILER ${ARM_TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_POSTFIX})
set(CMAKE_C_COMPILER ${ARM_TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc${TOOLCHAIN_POSTFIX})
set(CMAKE_CXX_COMPILER ${ARM_TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++${TOOLCHAIN_POSTFIX})


set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)