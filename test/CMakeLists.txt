set(CMAKE_CXX_FLAGS "-std=gnu++0x")

set(
	test_SRCS
	main.cpp
)

include_directories(
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
	"../src"
)

link_directories( ${CMAKE_SOURCE_DIR}/lib )

set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
   set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")

add_executable( testSuite ${test_SRCS} )
target_link_libraries( testSuite Baukasten cppunit )

install(TARGETS testSuite RUNTIME DESTINATION bin/)
install(DIRECTORY files DESTINATION bin/)
