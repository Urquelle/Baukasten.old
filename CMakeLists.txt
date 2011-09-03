cmake_minimum_required(VERSION 2.8)

project (Baukasten)

set (Baukasten_VERSION_MAJOR 0)
set (Baukasten_VERSION_MINOR 1)

set( Core_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core/include )
set( Graphics_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/include )
set( Input_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/input/include )
set( Core_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib )

add_subdirectory(src)
add_subdirectory(example)

find_package( Doxygen )
if (DOXYGEN_FOUND)
	set(DOXYGEN_INPUT Doxyfile)
	set(DOXYGEN_OUTPUT "${CMAKE_INSTALL_PREFIX}/doc")

	add_custom_command(
		OUTPUT ${DOXYGEN_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
		COMMAND ${CMAKE_COMMAND} -E echo "Done."
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${DOXYGEN_INPUT}
	)

	add_custom_target(doc DEPENDS ${DOXYGEN_OUTPUT})

	install(DIRECTORY doc/ DESTINATION ${DOXYGEN_OUTPUT})
endif(DOXYGEN_FOUND)
