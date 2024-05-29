cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_CXX_STANDARD 17)

file(GLOB src "./*.cpp" )
file(GLOB header "./*.h" )

include_directories(${root_dir}/3rdParty/eigen)
include_directories(${root_dir}/3rdParty/sophus)
include_directories(${root_dir}/AMCAXGCS)
include_directories(${root_dir}/GCS_sys)

add_executable(test_raw ${src} ${header})
target_link_libraries(test_raw AMCAXGCS3D)