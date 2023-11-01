add_library(sensor Sensor/sensor.c)

target_include_directories(sensor PRIVATE Sensor)

target_link_libraries(sensor PUBLIC compiler_flags)



add_library(RR RR/queue.c)

target_include_directories(RR PRIVATE Sensor)

target_link_libraries(RR PUBLIC compiler_flags)

add_subdirectory(Poly)
add_subdirectory(Event)
add_subdirectory(Observer)
add_subdirectory(Obs)
add_subdirectory(Event_states)
