add_library(poly animal.c dog.c)

target_include_directories(poly PRIVATE .)

target_link_libraries(poly PUBLIC compiler_flags)
