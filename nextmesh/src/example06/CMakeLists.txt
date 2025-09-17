cmake_minimum_required (VERSION 3.13 FATAL_ERROR)
project(test VERSION 1.0.0)
 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)


set(EXTERNAL_LIBS 
    AMCAXCommon
    AMCAXMeshing
    AMCAXPart
    AMCAXOCCTIO
    AMCAXNextMesh
    AMCAXStep
    AMCAXAF
)

file(GLOB files "*.cpp")
add_executable(test ${files})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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