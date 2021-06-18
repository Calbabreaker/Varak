add_library(VarakEvent src/event.h)

set_project_flags(VarakEvent)
target_include_directories(VarakEvent PRIVATE "src/")
target_include_directories(VarakEvent INTERFACE "./")
target_precompile_headers(VarakEvent REUSE_FROM VarakCore)
target_link_libraries(VarakEvent VarakCore)
