cmake_minimum_required(VERSION 3.15.3)

project(hardware VERSION 0.0.0
        LANGUAGES ASM C CXX)

# Project which will generate static library
# The purpose is that, it will be used of among multiple projects (I guess)

add_library(${PROJECT_NAME})
add_library("${PROJECT_NAMESPACE}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/inc
${CMAKE_CURRENT_SOURCE_DIR}/inc/CMSIS
${CMAKE_CURRENT_SOURCE_DIR}/inc/device
)

target_sources(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/src/cpp_config.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/semihost_hardfault.c
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )





