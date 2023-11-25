set(APP_SOURCES
               main.c
               run_state.c
               stop_state.c
               task.c
               task_state.c
			   process_state.c
			   )
			   
add_executable(task_test ${APP_SOURCES})
