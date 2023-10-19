# Create notes  scrible for quick test 
add_executable(observer
               main.c
               display_client.c
               gas_data.c
               gas_sensor.c
               gas_notification_handle.c
)

# Link FreeRTOS as a static library
message(${PROJECT_SOURCE_DIR})
target_include_directories(observer PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/Event"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          )

target_link_libraries(observer
                      PUBLIC 
                      # event
                      # RR
                      compiler_flags 
                    )


