cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME matrix)
project(${PROJECT_NAME} CXX)


# Конфигурация сборки
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)


# Общие пути
set(MP2_LIBRARY "${PROJECT_NAME}")
set(MP2_TESTS "test_${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MP2_GTEST "${CMAKE_CURRENT_SOURCE_DIR}/gtest")


add_library(${MP2_LIBRARY} INTERFACE)

target_sources(${MP2_LIBRARY} INTERFACE
    ${MP2_INCLUDE}/tmatrix.h
)

target_include_directories(${MP2_LIBRARY} INTERFACE
    ${MP2_INCLUDE}
    ${MP2_GTEST}
)


# Подпроекты
add_subdirectory(gtest)
add_subdirectory(samples)
add_subdirectory(test)


# Отчёт
message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}:")
message(STATUS "---------------------------------------------------------")
message(STATUS "  Configuration : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  C++ standard  : ${CMAKE_CXX_STANDARD}")
message(STATUS "  Include dir   : ${MP2_INCLUDE}")
message(STATUS "---------------------------------------------------------")
