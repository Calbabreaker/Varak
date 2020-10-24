file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)

add_executable(Sandbox ${SOURCES})

target_link_libraries(Sandbox Varak)
