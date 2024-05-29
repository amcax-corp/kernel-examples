cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(GCS3d)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}/bin)

if(DEFINED ENV{Boost_DIR})
  set(Boost_INCLUDE_DIR $ENV{Boost_DIR})
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost "1.83.0" COMPONENTS filesystem)
if(Boost_FOUND)
  add_subdirectory(test_assembly)
endif()

add_subdirectory(test_amcax_gcs)
add_subdirectory(test_gcs)
add_subdirectory(test_raw)
add_subdirectory(GCS2D.DotNet)