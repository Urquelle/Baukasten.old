cmake_minimum_required(VERSION 2.8)

project (Baukasten)

set(LIB_MAJOR 0)
set(LIB_MINOR 2)
set(LIB_PATCH 0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions( -DLIB_MAJOR=${LIB_MAJOR} -DLIB_MINOR=${LIB_MINOR} -DLIB_PATCH=${LIB_PATCH} )
set(CMAKE_CXX_FLAGS "-std=gnu++0x")

if( NOT ( CMAKE_BUILD_TYPE STREQUAL Debug ) )
	add_definitions( -DNDEBUG )
endif()

option( WITH_DOC "add documentation." FALSE )

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)

if( WITH_DOC )
	set(DOXYFILE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
	set(DOXYFILE_OUTPUT_DIR ${CMAKE_INSTALL_PREFIX}/doc)
	include(UseDoxygen)
endif( WITH_DOC )
