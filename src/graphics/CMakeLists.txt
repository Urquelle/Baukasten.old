set( GRAPHICS_INC ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include )

set (
	graphics_SRCS
	graphics/src/graphics_interface.cpp
	graphics/src/irrlicht/irrlicht_graphics.cpp
	graphics/src/irrlicht/irrlicht_form.cpp
)

if( WITH_OGRE )
	set(
		${graphics_SRCS}
		${graphics_SRCS}
		graphics/src/ogre/ogre_interface.cpp
		graphics/src/ogre/ogre_form.cpp
	)
endif()

