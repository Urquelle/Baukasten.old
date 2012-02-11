set( GRAPHICS_INC ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include )

include_directories( "/usr/include/freetype2" )

set (
	graphics_SRCS
	graphics/src/colour.cpp
	graphics/src/font.cpp
	graphics/src/graphics_interface.cpp
	graphics/src/glfw/glfw_graphics.cpp
)
