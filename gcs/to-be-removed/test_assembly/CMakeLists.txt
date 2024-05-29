cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost "1.83.0" REQUIRED COMPONENTS filesystem)

include_directories($ENV{Boost_DIR})
include_directories(${root_dir}/3rdParty/eigen)
include_directories(${root_dir}/3rdParty/sophus)
include_directories(${root_dir}/GCS_sys)
link_directories(${Boost_LIBRARY_DIRS})

set(src "test_assembly.cpp")

add_executable(test_assembly ${src})

target_link_libraries(test_assembly AMCAXGCS3D)
target_link_libraries(test_assembly sophus)
target_link_libraries(test_assembly nlopt)
target_link_libraries(test_assembly Boost::filesystem)