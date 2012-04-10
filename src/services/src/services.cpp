#include "services/Services"

#include "audio/IAudio"
#include "core/Debug"
#include "graphics/IGraphics"
#include "input/IInput"

using namespace Baukasten;

Services&
Services::instance()
{
	static Services instance;
	return instance;
}

Services::Services() :
	m_audio( AudioInterface::instance() ),
	m_graphics( GraphicsInterface::instance() ),
	m_input( InputInterface::instance() )
{
}

Services::~Services()
{
	BK_DEBUG( "destroy Services" );
	m_audio->shutdown();
	m_graphics->shutdown();
	m_input->shutdown();
}

void
Services::init( int argc, char** argv )
{
	m_argc = argc;
	m_argv = argv;

	m_audio->init( *this );
	m_graphics->init( *this );
	m_input->init( *this );
}

void
Services::shutdown()
{
	m_input->shutdown();
	m_graphics->shutdown();
	m_audio->shutdown();
}

IAudio&
Services::audioService() const
{
	return *m_audio;
}

IInput&
Services::inputService() const
{
	return *m_input;
}

IGraphics&
Services::graphicsService() const
{
	return *m_graphics;
}

int
Services::argc()
{
	return m_argc;
}

char**
Services::argv() const
{
	return m_argv;
}

