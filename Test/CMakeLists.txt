# -----------------------------------
# TESTS
# minimal unit ctest


enable_testing()

add_executable(tests tests.c)

# The order is VERY importnet (else Lineker will not work)
target_link_libraries(tests
        cmocka-static
        )
# Include for ctests
# target_include_directories(tests PUBLIC
      # ${PROJECT_SOURCE_DIR}/Simulation/inc)

# target_compile_options(tests PRIVATE -fsanitize=undefined,leak,address)
# target_link_options(tests PRIVATE -fsanitize=undefined,leak,address) 

# invoke command tests
add_test(NAME tests COMMAND tests)

add_custom_target(
  test
  COMMAND ctest --verbose
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running tests ...."
  VERBATIM
  )

add_dependencies(test tests)

