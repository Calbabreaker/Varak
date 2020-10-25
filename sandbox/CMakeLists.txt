project(Sandbox VERSION 1.0.0)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(Sandbox ${SOURCES})

target_link_libraries(Sandbox Varak)
