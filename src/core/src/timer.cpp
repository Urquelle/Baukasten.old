#include "core/include/timer.h"

#include <ctime>

namespace Baukasten {

/*!
 * \brief TimerPrivate class declaration.
 */
class TimerPrivate {
public:
	TimerPrivate() :
		m_elapsed( 0 ), m_paused( false ), m_scale( 1.0f ),
		m_time( 0 ), m_res( 1e-9 )
	{
	}

	void
	reset()
	{
		m_time = _gettime();
		m_elapsed = 0;
	}

	void
	start()
	{
		m_time = _gettime();
		m_elapsed = 0;
	}

	void
	setPause( bool pause )
	{
		m_paused = pause;
	}

	bool
	isPaused() const
	{
		return m_paused;
	}

	void
	setTimeScale( const f32 scale )
	{
		m_scale = scale;
	}

	f32
	timeScale() const
	{
		return m_scale;
	}

	u64
	cycles() const
	{
		return m_elapsed;
	}

	f32
	time() const
	{
		return m_elapsed * m_res;
	}

	void
	update()
	{
		if ( !m_paused ) {
			m_elapsed = ( _gettime() - m_time ) * m_scale;
		}
	}

private:

	inline u64 _gettime()
	{
		clock_gettime( CLOCK_MONOTONIC, &m_t );
		return (u64)m_t.tv_sec * (u64)1000000000 + (u64)m_t.tv_nsec;
	}

	u64       m_elapsed;
	bool      m_paused;
	f32       m_scale;
	u64       m_time;
	timespec  m_t;
	const f32 m_res;
};

Timer::Timer() :
	m_impl( new TimerPrivate() )
{
}

Timer::~Timer()
{
	delete m_impl;
}

void
Timer::reset()
{
	m_impl->reset();
}

void
Timer::start()
{
	m_impl->start();
}

void
Timer::setPause( bool pause )
{
	m_impl->setPause( pause );
}

bool
Timer::isPaused() const
{
	return m_impl->isPaused();
}

void
Timer::setTimeScale( const f32 scale )
{
	m_impl->setTimeScale( scale );
}

f32
Timer::timeScale() const
{
	return m_impl->timeScale();
}

u64
Timer::cycles() const
{
	return m_impl->cycles();
}

f32
Timer::time() const
{
	return m_impl->time();
}

void
Timer::update()
{
	m_impl->update();
}

}
