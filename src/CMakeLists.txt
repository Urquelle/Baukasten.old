option( WITH_LUA  "compile with Lua support." TRUE )

include( audio/CMakeLists.txt )
include( core/CMakeLists.txt )
include( graphics/CMakeLists.txt )
include( input/CMakeLists.txt )
include( model/CMakeLists.txt )
include( util/CMakeLists.txt )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

link_directories(
	${slb_LINKDIR}
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

add_definitions( -DEXPORT_LIB=1 -Wall )
add_library( Baukasten SHARED ${model_SRCS} ${core_SRCS} ${audio_SRCS}
	${graphics_SRCS} ${input_SRCS} ${util_SRCS} )

set_target_properties( Baukasten PROPERTIES SOVERSION 0.0.1 )

target_link_libraries( Baukasten sigc-2.0 SLB openal png jpeg  alut GL GLEW GLU glfw freetype )

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
	DIRECTORY model/
	DESTINATION ${CMAKE_INSTALL_PREFIX}/model
	PATTERN *.cpp EXCLUDE
	PATTERN *.txt EXCLUDE
)

install(TARGETS Baukasten LIBRARY DESTINATION lib/)
