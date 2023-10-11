# Path to your MinGW compiler
# set(MINGW_TOOLCHAIN_PATH "C:/MinGW/bin/")
find_program(MINGW_COMPILER gcc PATHS ${MINGW_TOOLCHAIN_PATH})

# -> CC := gcc 
set(CMAKE_C_COMPILER "${MINGW_COMPILER}")

find_program(CMAKE_AR gcc-ar PATHS ${MINGW_TOOLCHAIN_PATH})
find_program(CMAKE_LINKER ld PATHS ${MINGW_TOOLCHAIN_PATH})
find_program(CMAKE_AS as PATHS ${MINGW_TOOLCHAIN_PATH})
find_program(MINGW_EDITELF elfedit PATHS ${MINGW_TOOLCHAIN_PATH})
message(STATUS "CC: ${CMAKE_C_COMPILER}")
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# if(NOT EXISTS "${ARMCC_FROMELF}")
    # message(STATUS ${ARMCC_FROMELF})
    # message(FATAL_ERROR "ARMCC toolchain is not found, please set ARMCC_TOOLCHAIN_PATH variable correctly")
# endif()
