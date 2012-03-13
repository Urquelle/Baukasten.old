cmake_minimum_required(VERSION 2.8)

project (Baukasten)

set(LIB_MAJOR 0)
set(LIB_MINOR 1)
set(LIB_PATCH 0)

add_definitions( -DLIB_MAJOR=${LIB_MAJOR} -DLIB_MINOR=${LIB_MINOR} -DLIB_PATCH=${LIB_PATCH} )
set(CMAKE_CXX_FLAGS "-std=gnu++0x")

if( NOT ( CMAKE_BUILD_TYPE STREQUAL Debug ) )
	add_definitions( -DNDEBUG )
endif()

option( WITH_DOC  "add documentation." FALSE )

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)

if( WITH_DOC )
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
endif( WITH_DOC )
