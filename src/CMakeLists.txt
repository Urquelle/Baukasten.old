option( WITH_LUA  "compile with Lua support." TRUE )
option( WITH_OGRE  "compile with OGRE support." TRUE )

if( WITH_OGRE )
	add_definitions( -DWITH_OGRE )
endif()

include( core/CMakeLists.txt )
include( graphics/CMakeLists.txt )
include( input/CMakeLists.txt )

include_directories( ${CORE_INC} ${GRAPHICS_INC} ${INPUT_INC} )
link_directories(
	${slb_LINKDIR}
	"/usr/include/sigc++-2.0"
	"/usr/lib64/sigc++-2.0/include"
)

add_definitions( -DEXPORT_LIB=1 )
add_library( Baukasten SHARED ${core_SRCS} ${graphics_SRCS} ${input_SRCS} )

set_target_properties( Baukasten PROPERTIES SOVERSION 0.0.1 )

target_link_libraries( Baukasten sigc-2.0 SDL )

install(DIRECTORY core/include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install(TARGETS Baukasten LIBRARY DESTINATION lib/)
install(FILES ${core_HEADER} DESTINATION include/)
