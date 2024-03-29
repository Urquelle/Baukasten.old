option( WITH_LUA  "compile with Lua support." TRUE )

if( ASSERTIONS_ENABLED )
	add_definitions( -DASSERTIONS_ENABLED )
endif()

include( audio/CMakeLists.txt )
include( core/CMakeLists.txt )
include( graphics/CMakeLists.txt )
include( input/CMakeLists.txt )
include( io/CMakeLists.txt )
include( math/CMakeLists.txt )
include( model/CMakeLists.txt )
include( services/CMakeLists.txt )
include( util/CMakeLists.txt )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

link_directories(
	${slb_LINKDIR}
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

add_definitions( -DEXPORT_LIB=1 -Wall )

add_library( Baukasten SHARED
	${audio_SRCS}
	${core_SRCS}
	${graphics_SRCS}
	${input_SRCS}
	${io_SRCS}
	${math_SRCS}
	${model_SRCS}
	${services_SRCS}
	${util_SRCS}
)

set_target_properties( Baukasten PROPERTIES SOVERSION
	${LIB_MAJOR}.${LIB_MINOR}.${LIB_PATCH} )

target_link_libraries( Baukasten sigc-2.0 SLB freeimage openal alut GL GLEW GLU glfw freetype )

install(
	DIRECTORY audio/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/audio
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY core/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/core
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY graphics/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/graphics
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY input/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/input
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY math/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/math
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY model/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/model
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(
	DIRECTORY util/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/util
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(TARGETS Baukasten LIBRARY DESTINATION lib)
