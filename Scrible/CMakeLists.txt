# Create notes  scrible for quick test 
add_executable(notes
               notes.c
)

# Link FreeRTOS as a static library
message(${PROJECT_SOURCE_DIR})
target_include_directories(notes PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/Poly"
                          )

target_link_libraries(notes
                      PUBLIC 
                      poly
                      compiler_flags 
                    )


