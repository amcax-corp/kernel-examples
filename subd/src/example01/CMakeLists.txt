cmake_minimum_required (VERSION 3.13 FATAL_ERROR)
project(test VERSION 1.0.0)
 
set(EXTERNAL_LIBS 
    AMCAXCommon
    AMCAXSubD
)

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

if(MSVC)
  set_target_properties(test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;${AMCAXCommon_RUNTIME_DIR};${AMCAXPart_RUNTIME_DIR}")
endif()