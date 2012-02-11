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

link_directories( ${Core_LIB_DIR} ${CMAKE_INSTALL_PREFIX}/lib )

add_executable( testSuite ${test_SRCS} )
target_link_libraries( testSuite Baukasten SLB cppunit png jpeg bz2 )
install(TARGETS testSuite RUNTIME DESTINATION bin/)
