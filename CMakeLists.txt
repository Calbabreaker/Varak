cmake_minimum_required(VERSION 3.16)

project(Varak VERSION 1.0.0)

add_subdirectory(varak)
add_subdirectory(sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE) 
