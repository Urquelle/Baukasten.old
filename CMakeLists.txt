cmake_minimum_required(VERSION 2.8)

project (Baukasten)

set (Baukasten_VERSION_MAJOR 0)
set (Baukasten_VERSION_MINOR 1)

add_subdirectory(src)

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

	add_custom_target(doc ALL DEPENDS ${DOXYGEN_OUTPUT})

	install(DIRECTORY doc/ DESTINATION ${DOXYGEN_OUTPUT})
endif(DOXYGEN_FOUND)
