include_directories(
	${Core_INCLUDE_DIR}
	${Graphics_INCLUDE_DIR}
	${Input_INCLUDE_DIR}
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

link_directories( ${Core_LIB_DIR} ${CMAKE_INSTALL_PREFIX}/lib )

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")

add_subdirectory( tetris )
