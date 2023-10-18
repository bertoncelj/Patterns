add_library(event event.c)

target_link_libraries(event PUBLIC 
                              RR 
                              compiler_flags
                              )

target_include_directories(event PUBLIC
                          .
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          )
