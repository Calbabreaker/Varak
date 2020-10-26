cmake_minimum_required(VERSION 3.16)

project(VarakEngine VERSION 1.0.0)

add_subdirectory(varak)
add_subdirectory(sandbox)

set(CMAKE_CXX_STANDARD 17)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
