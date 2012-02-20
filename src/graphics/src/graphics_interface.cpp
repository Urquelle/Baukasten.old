#include "graphics/GraphicsInterface"

#include "graphics/GraphicsImpl"
#include "graphics/IGraphics"

using namespace Baukasten;

IGraphics* GraphicsInterface::m_instance = 0;

IGraphics*
GraphicsInterface::instance()
{
	if ( !m_instance ) {
		m_instance = new Graphics();
	}

	return m_instance;
}

