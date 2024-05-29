cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories($ENV{Boost_DIR})
include_directories(${root_dir}/3rdParty/eigen)
include_directories(${root_dir}/3rdParty/sophus)
include_directories(${root_dir}/AMCAXGCS)
link_directories(${Boost_LIBRARY_DIRS})

set(src "main.cpp")

add_executable(test_amcax_gcs ${src})

target_link_libraries(test_amcax_gcs AMCAXGCS)
target_link_libraries(test_amcax_gcs sophus)
target_link_libraries(test_amcax_gcs nlopt)
target_link_libraries(test_amcax_gcs Boost::filesystem)