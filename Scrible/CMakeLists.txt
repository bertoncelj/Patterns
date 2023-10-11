# Create notes  scrible for quick test 
add_executable(notes
               notes.c
)

# Link FreeRTOS as a static library
target_link_libraries(notes

               INTERFACE
               compiler_flags
               )

