# Create notes  scrible for quick test 
add_executable(obs
               main.c
               client.c
               subject.c
)

# Link FreeRTOS as a static library
message(${PROJECT_SOURCE_DIR})
target_include_directories(obs PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/Event"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          )

target_link_libraries(obs
                      PUBLIC 
                      # event
                      # RR
                      compiler_flags 
                    )


