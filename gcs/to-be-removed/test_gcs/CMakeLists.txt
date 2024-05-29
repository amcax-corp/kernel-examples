cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_CXX_STANDARD 17)

include_directories($ENV{BOOST_DIR})
include_directories(${root_dir}/3rdParty/eigen)
include_directories(${root_dir}/3rdParty/sophus)
include_directories(${root_dir}/GCS_sys)

file(GLOB cpp "*.cpp")
file(GLOB h "*.h")

add_executable(test_gcs ${cpp} ${h})

target_link_libraries(test_gcs AMCAXGCS3D)
target_link_libraries(test_gcs sophus)
target_link_libraries(test_gcs nlopt)