cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(Varak LANGUAGES CXX C)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/yacpm.cmake")
    file(DOWNLOAD "https://github.com/Calbabreaker/yacpm/raw/v3/yacpm.cmake" "${CMAKE_BINARY_DIR}/yacpm.cmake")
endif()

include(${CMAKE_BINARY_DIR}/yacpm.cmake)
yacpm_use_extended()

add_subdirectory(varak)
add_subdirectory(varak_editor)
