# Create notes  scrible for quick test 
add_executable(observer1
               main_app.c
               display_client.c
               gas_sensor.c
	             gas_mixer_client.c
)

# Link FreeRTOS as a static library
message(${PROJECT_SOURCE_DIR})
target_include_directories(observer1 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Lib/Event"
                          "${PROJECT_SOURCE_DIR}/Lib/RR"
                          )

target_link_libraries(observer1
                      PUBLIC 
                      compiler_flags 
                    )


