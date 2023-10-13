add_library(poly animal.c dog.c cat.c)

target_include_directories(poly PRIVATE .)

target_link_libraries(poly PUBLIC compiler_flags)
