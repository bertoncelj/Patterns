find_package(Doxygen REQUIRED)

if(DOXYGEN_FOUND)
    message("start doxygen generation ...")
    add_custom_target(
        docs
        COMMAND doxygen ${PROJECT_SOURCE_DIR}/Docs/Doxyfile
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/Docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
        )
endif()

