cmake_minimum_required(VERSION 3.15.3)

project(drivers_tests VERSION 0.0.0
		LANGUAGES ASM C CXX)

add_executable(${PROJECT_NAME})
        
        
target_include_directories(${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/inc)
        
target_sources(${PROJECT_NAME}
PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/src/clocks_tests.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/reg_tests.cpp

${CMAKE_CURRENT_SOURCE_DIR}/drivers_tests.cpp
)
        
# Also lets get rid of int main() missing declarations warning
set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/drivers_tests.cpp
PROPERTY
COMPILE_FLAGS -Wno-missing-declarations)
        
target_link_libraries(${PROJECT_NAME}
PRIVATE
"${PROJECT_NAMESPACE}::drivers"
"${PROJECT_NAMESPACE}::tests"
"${PROJECT_NAMESPACE}::utility"
)
       
        
install(TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION out)
        
        
        
        
        