# NOTE: It can parse source and include file, but
# working with defines it does not parse correctly, it can be
# that in a project is not specificated under target build but only in
# header files

# Goes over subdirs and parse project files and dependency
function(tags_add_dir _dir)

	# Get all sub_directories called from root cmake
	get_property(_subdirlist DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)

	# Recursevly goes in and parse project properties for each sub_dir
	foreach(_sd ${_subdirlist})
		tags_add_dir(${_sd})
	endforeach()

	# Get all executable or lib names to execute in _target_list
	get_property(_targets_list DIRECTORY "${_dir}" PROPERTY BUILDSYSTEM_TARGETS)

	# For each target find properties, includes, defines ... 
	foreach(_tgt ${_targets_list})
		get_property(_t_cflags TARGET ${_tgt} PROPERTY COMPILE_FLAGS)
		get_property(_t_files  TARGET ${_tgt} PROPERTY SOURCES)
		get_property(_t_defs   TARGET ${_tgt} PROPERTY COMPILE_DEFINITIONS)
    get_target_property(_target_dir ${_tgt} SOURCE_DIR)
    get_target_property(_incld_dir  ${_tgt} INCLUDE_DIRECTORIES)

		# If a file have a full path specificated like C:/bla/bla/file.c
		# Remove so it can have a only file.c
		# We do this trick so each full path file or just file will have
		# in the end same path
		string(REGEX REPLACE "${_target_dir}/" "" _t_files "${_t_files}")
		
		# Append full path to each file 
		list(TRANSFORM _t_files  PREPEND "${_target_dir}/")

		# If Include directire is not specificated it will return NOTFOUND, so we remove it
		string(REGEX REPLACE "${_incld_dir}-NOTFOUND" "" _incld_dir "${_incld_dir}")

    # Append include directories to path so ctgas can find it
    if(NOT "${_incld_dir}" STREQUAL "_incld_dir-NOTFOUND")
			list(APPEND _all_source_files ${_incld_dir})
    endif()

		# Append all source files
		list(APPEND _all_source_files ${_t_files})

		# TODO: remove it, idk why is this here
		string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" _t_files "${_t_files}")
		string(REGEX REPLACE "${CMAKE_SOURCE_DIR}/" "" _t_files "${_t_files}")
		string(REGEX REPLACE ";" "\n" _t_files "${_t_files}")

		# Parse defines 
		string(REGEX REPLACE ";" "\n" _t_defs "${_t_defs}")
		string(REGEX REPLACE "^([^=]+)$" "\\1=1" _t_defs "${_t_defs}")
	endforeach()
	# Save all into gloval scope of this file outside of function
	set(_all_source_files ${_all_source_files} PARENT_SCOPE)
	set(_all_definitions ${_all_definitions} PARENT_SCOPE)
endfunction()

# Start program:

# Check if ctags is in Build directory
set(CTAGS_DIR "${CMAKE_BINARY_DIR}/ctags") 
set(CTAGS_EXE "${CTAGS_DIR}/ctags.exe")

find_program(CTAGS ${CTAGS_EXE})

if(NOT EXISTS ${CTAGS_EXE})
    message(STATUS "ctags.exe not found. Initiating download...")

   # Download the identified asset
    file(DOWNLOAD "https://github.com/universal-ctags/ctags-win32/releases/download/v6.0.0/ctags-v6.0.0-x64.zip" "${CMAKE_BINARY_DIR}/ctags_x64.zip" SHOW_PROGRESS)

    # Extract the zip to the project directory
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_BINARY_DIR}/ctags_x64.zip"
         DESTINATION "${CMAKE_BINARY_DIR}/ctags")

endif()

# If Ctags was is ON 
if(CTAGS)
	# All Source files and defines that must be compiled for project will be in .lst files
	set(SOURCES_LIST "${CMAKE_BINARY_DIR}/source_files.lst")
	set(CTAGS_IDENTIFIER_LIST "${CMAKE_BINARY_DIR}/identifier.lst")

	# Create a global variable so tags_add_dir will fill it
	set(_all_source_files "")
	set(_all_definitions "")

	# Remove old files.lst
	file(REMOVE "${SOURCES_LIST}")
	file(REMOVE "${CTAGS_IDENTIFIER_LIST}")

	# Start looking recursevly sub_directories() from root of project
	tags_add_dir(${CMAKE_SOURCE_DIR})

	list(SORT _all_source_files)
	list(REMOVE_DUPLICATES _all_source_files)

	# Remove only root path from full path to a sub_dir file C:/path_to_proj/subdir/file -> subdir/file
	string(REGEX REPLACE "${CMAKE_SOURCE_DIR}/" "" _asf "${_all_source_files}")

	# Goes from variables file1;file2; to newline in file
	string(REGEX REPLACE ";" "\n" _asf "${_asf}")

	# Write into file.lst all paths sources and includes
	file(APPEND ${SOURCES_LIST} "\n${_asf}")

	# Same for extras and append to source_file.lst
	string(REGEX REPLACE "${CMAKE_SOURCE_DIR}/" "" _t_extra "${TAGS_EXTRA_FILES}")
	string(REGEX REPLACE ";" "\n" _t_extra "${_t_extra}")
	file(APPEND ${SOURCES_LIST} "\n${_t_extra}")

	# Same for defines and append to definitions.lst
	string(REGEX REPLACE ";" "\n" _all_definitions "${_all_definitions}")
	string(REGEX REPLACE "^([^=]+)$" "\\1=1" _all_definitions "${_all_definitions}")
	file(APPEND ${CTAGS_IDENTIFIER_LIST} "\n${_all_definitions}")

	add_custom_target(tags ALL)
endif()

if(CTAGS)
	if (NOT CTAGS_TAG_FILE)
		set(CTAGS_TAG_FILE "${CMAKE_SOURCE_DIR}/tags" CACHE STRING "ctags output file")
	endif()

	# Run ctags command and creat tags in project root
	add_custom_target(ctags
		COMMAND ${CTAGS_EXE} --extra=+q --c-kinds=+lpx --fields=afikmsSzt
		-I ${CTAGS_IDENTIFIER_LIST} -f ${CTAGS_TAG_FILE} -L ${SOURCES_LIST}
		DEPENDS ${_all_source_files}
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		VERBATIM)

	add_dependencies(tags ctags)
endif()
