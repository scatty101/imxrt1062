cmake_minimum_required(VERSION 3.15.3)

# We are cross compiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

project(imxrt1062 VERSION 0.0.0
        LANGUAGES ASM C CXX)


set(PROJECT_NAMESPACE imxrt1062)

# Languages def
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Instalation directory for every subdirectory
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Common 


# C compile flags for subprojects. 




# CXX compile flags for subprojects


# Linker flags for subprojects

# Common defs

# Adding subprojects
add_subdirectory(hardware)



