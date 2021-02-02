cmake_minimum_required(VERSION 3.15.3)

project(tests)


add_library(${PROJECT_NAME})
add_library(${PROJECT_NAMESPACE}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Based on gtest-port.h 
# Well, its bare metal, lets that we don't have any of these
target_compile_definitions(${PROJECT_NAME}
PRIVATE
-DGTEST_HAS_CLONE=0          
-DGTEST_HAS_EXCEPTIONS=0     
-DGTEST_HAS_POSIX_RE=0       
-DGTEST_HAS_PTHREAD=0        
-DGTEST_HAS_RTTI=0           
-DGTEST_HAS_STD_WSTRING=0    
-DGTEST_HAS_SEH=0            
-DGTEST_HAS_STREAM_REDIRECTION=0
-DGTEST_LINKED_AS_SHARED_LIBRARY=0
-DGTEST_CREATE_SHARED_LIBRARY=0
-DGTEST_OS_NONE
-DGTEST_HAS_DEATH_TEST=0
)

target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include

${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/
${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
)

# We can use gtest-all.cc and gmock-all.cc, as its includes other source files
target_sources(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/gtest-completion.c
${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc
${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/src/gmock-all.cc
)

set_property(SOURCE gtest-all.cc gmock-all.cc
APPEND_STRING
PROPERTY 
COMPILE_FLAGS " -Wno-psabi -Wno-pedantic -Wno-missing-declarations")

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)