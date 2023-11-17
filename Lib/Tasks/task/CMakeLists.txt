add_executable(task_test
               main.c
               run_state.c
               stop_state.c
               task.c
               task_state.c
               post_run_state.c
)

target_include_directories(task_test PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          )

target_link_libraries(task_test
                      PUBLIC 
                      compiler_flags 
                    )




