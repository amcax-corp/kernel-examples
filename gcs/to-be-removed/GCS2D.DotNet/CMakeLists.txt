cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)

include_directories(
	${root_dir}/3rdParty/eigen
	${root_dir}/3rdParty/sophus
	${root_dir}/GCS_sys
)

file(GLOB source_file "./*.cpp")
file(GLOB header_file "./*.h" )

add_library(GCS2D.DotNet SHARED ${source_file} ${header_file})

target_link_libraries(GCS2D.DotNet AMCAXGCS3D)