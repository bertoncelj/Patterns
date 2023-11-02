add_library(output output.c)

target_link_libraries(output PUBLIC 
                              RR 
                              compiler_flags
                              )

target_include_directories(output PUBLIC
                          .
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          )
