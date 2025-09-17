cmake_minimum_required (VERSION 3.13 FATAL_ERROR)
project(test VERSION 1.0.0)
 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)


set(EXTERNAL_LIBS 
    AMCAXPart
    AMCAXCommon
    AMCAXAF
    AMCAXOCCTIO
    AMCAXStep
)
find_package(OpenMP REQUIRED)
if (OpenMP_FOUND)
  message(STATUS "add ${OpenMP_C_FLAGS}")
  set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  #target_link_libraries(test PRIVATE OpenMP::OpenMP_CXX)
endif()

add_compile_definitions(NOMINMAX)

file(GLOB files "*.cpp")
add_executable(test ${files})

foreach(LIB ${EXTERNAL_LIBS})
    find_package(${LIB} REQUIRED)
    target_link_libraries(test ${LIB})
    
    get_filename_component(LIB_ROOT_DIR "${${LIB}_DIR}" PATH)
    set(DLL_PATH "${LIB_ROOT_DIR}/../../bin/$<CONFIG>/${LIB}.dll")

   # message("AMCAXCommon_DIR ${${LIB}_DIR} ; ${LIB}_")
    add_custom_command(
        TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_PATH}"
            $<TARGET_FILE_DIR:test>
    )
endforeach()

add_custom_command(
    TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:test>/data
)



if(MSVC)
  set_target_properties(test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${AMCAXCommon_RUNTIME_DIR};${AMCAXPart_RUNTIME_DIR}")
endif()