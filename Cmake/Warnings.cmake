set(GCC_FLAGS
     -Wall
     # Check the code for syntax errors, but don’t do anything beyond that.
     # -fsyntax-only
     # This enables some extra warning flags that are not enabled by -Wall.
     -Wextra
     -Wformat
     # Warning for unused variables
     -Wunused
     # If TARGET_SET_WARNINGS_AS_ERRORS enabled, warnings become errors
     $<$<BOOL:${ENABLE_WARNINGS_AS_ERRORS}>:-Werror>
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE c_std_99)
# add compiler warning flags just when building this project via
# the BUILD_INTERFACE genex
set(gcc_like_c "$<COMPILE_LANG_AND_ID:C,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_c "$<COMPILE_LANG_AND_ID:C,MSVC>")

target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_c}:$<BUILD_INTERFACE:${GCC_FLAGS};>>"
  "$<${msvc_c}:$<BUILD_INTERFACE:-W3>>"
  "$<$<CONFIG:Debug>:-O0>"
  "$<$<CONFIG:Release>:-O3>"
  
)

