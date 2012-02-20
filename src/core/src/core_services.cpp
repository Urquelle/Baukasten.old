#include "core/CoreServices"

#include "audio/IAudio"
#include "core/Debug"
#include "graphics/IGraphics"
#include "input/IInput"

using namespace Baukasten;

CoreServices*
CoreServices::instance()
{
	static CoreServices instance;
	return &instance;
}

CoreServices::CoreServices() :
	m_audio( AudioInterface::instance() ),
	m_graphics( GraphicsInterface::instance() ),
	m_input( InputInterface::instance() )
{
}

CoreServices::~CoreServices()
{
	BK_DEBUG( "destroy CoreServices" );
	m_audio->shutdown();
	m_graphics->shutdown();
	m_input->shutdown();
}

void
CoreServices::init( int argc, char* argv[] )
{
	m_argc = argc;
	m_argv = argv;

	m_audio->init( this );
	m_graphics->init( this );
	m_input->init( this );
}

void
CoreServices::shutdown()
{
	m_input->shutdown();
	m_graphics->shutdown();
	m_audio->shutdown();
}

IAudio*
CoreServices::audioService() const
{
	return m_audio;
}

IInput*
CoreServices::inputService() const
{
	return m_input;
}

IGraphics*
CoreServices::videoService() const
{
	return m_graphics;
}

int
CoreServices::argumentsCount()
{
	return m_argc;
}

char**
CoreServices::arguments() const
{
	return m_argv;
}

