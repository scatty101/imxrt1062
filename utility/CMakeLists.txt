cmake_minimum_required(VERSION 3.15.3)


project(utility VERSION 0.0.0
        LANGUAGES CXX)

add_library(${PROJECT_NAME})
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/inc
)


target_sources(${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src/useless.cpp
)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )
