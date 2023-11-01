add_executable(event_state 
            main.c
            digi.c
            state_stop.c
            state_start.c
            watch_state.c
            )

target_link_libraries(event_state PUBLIC 
                              compiler_flags
                              )

target_include_directories(event_state PUBLIC
                          .
                          "${PROJECT_BINARY_DIR}"
                          )
