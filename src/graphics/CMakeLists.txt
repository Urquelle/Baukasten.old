include_directories( "/usr/include/freetype2" )

set (
	graphics_SRCS
	graphics/src/glfw/gl_texture.cpp
	graphics/src/glfw/gl_font.cpp
	graphics/src/glfw/gl_mesh.cpp
	graphics/src/glfw/glfw_graphics.cpp
	graphics/src/glfw/node.cpp
	graphics/src/graphics_interface.cpp
	graphics/src/image.cpp
	graphics/src/imesh.cpp
)
