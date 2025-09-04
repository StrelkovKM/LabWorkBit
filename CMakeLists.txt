cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME LabWorkBit)
project(${PROJECT_NAME})

# TODO(Korniakov): not sure if these lines are needed
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(BIT_LIBRARY "${PROJECT_NAME}")
set(BIT_TESTS   "${PROJECT_NAME}")
set(BIT_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/BitInclude")

include_directories("${BIT_INCLUDE}" gtest)

# BUILD
add_subdirectory(BitLib)
add_subdirectory(BitApp)
add_subdirectory(gtest)
add_subdirectory(BitTest)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")
