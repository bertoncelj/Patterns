add_library(event 
            ${PROJECT_SOURCE_DIR}/Lib/Tasks/task_led.c
            event.c
            event_table.c)

target_link_libraries(event PUBLIC 
                              output
                              RR 
                              compiler_flags
                              )

target_include_directories(event PUBLIC
                          .
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          "${PROJECT_SOURCE_DIR}/Lib/Tasks"
                          "${PROJECT_SOURCE_DIR}/Lib/Output"
                          )
