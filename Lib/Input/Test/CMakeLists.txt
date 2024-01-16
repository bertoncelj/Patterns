# -----------------------------------
# TESTS
# minimal unit ctest


enable_testing()

add_executable(test_input input_test.c)

# The order is VERY importnet (else Lineker will not work)
target_link_libraries(test_input
        compiler_flags
        cmocka-static
        )
# Include for ctests
# target_include_directories(tests PUBLIC
  # ${PROJECT_SOURCE_DIR}/Lib/RR)

# target_compile_options(tests PRIVATE -fsanitize=undefined,leak,address)
# target_link_options(tests PRIVATE -fsanitize=undefined,leak,address) 

# invoke command tests
add_test(NAME test_input COMMAND test_input)

add_custom_target(
  test_input1
  COMMAND ctest --verbose
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running tests ...."
  VERBATIM
  )

add_dependencies(test_input test_input)

