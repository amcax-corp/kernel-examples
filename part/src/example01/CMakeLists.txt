cmake_minimum_required (VERSION 3.13 FATAL_ERROR)
project(test VERSION 1.0.0)
 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)

find_package(AMCAXCommon REQUIRED)
find_package(AMCAXPart REQUIRED)

file(GLOB files "*.cpp")
add_executable(test ${files})
target_link_libraries(test AMCAXPart AMCAXCommon)

if(MSVC)
  set_target_properties(test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${AMCAXCommon_RUNTIME_DIR};${AMCAXPart_RUNTIME_DIR}")
endif()