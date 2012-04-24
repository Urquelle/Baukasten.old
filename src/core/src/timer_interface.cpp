#include "core/include/timer_interface.h"

#include "core/Assert"
#include "core/Timer"

#include <algorithm>
#include <map>
#include <vector>

namespace Baukasten {

using namespace std;

/*!
 * \break TimerInterfacePrivate class declaration.
 */
class TimerInterfacePrivate {
public:
	TimerInterfacePrivate()
	{
	}

	virtual ~TimerInterfacePrivate()
	{
	}

	Timer& createTimer( const string &id )
	{
		BK_ASSERT( m_timer.count( id ) == 0,
				"given id ( " << id << " ) already in the collection." );

		Timer *timer = new Timer();
		m_timer[ id ] = timer;
		m_list.push_back( timer );

		return *timer;
	}

	Timer& timer( const string &id )
	{
		BK_ASSERT( m_timer.count( id ) > 0, "given id not in the collection." );
		return ( *m_timer[ id ] );
	}

	void destroyTimer( const string &id )
	{
		BK_ASSERT( m_timer.count( id ) > 0, "given id not in the collection." );

		Timer *timer = m_timer[ id ];

		m_timer.erase( id );
		m_list.erase( find( m_list.begin(), m_list.end(), timer ) );

		delete timer;
	}

	void updateAll() const
	{
		for ( size_t i = 0; i < m_list.size(); ++i ) {
			m_list[i]->update();
		}
	}

private:
	map<string, Timer*> m_timer;
	vector<Timer*>      m_list;
};

TimerInterface* TimerInterface::m_instance = 0;

TimerInterface*
TimerInterface::instance()
{
	if ( !m_instance ) {
		m_instance = new TimerInterface();
		m_instance->createTimer( "system:main" ).start();
	}

	return m_instance;
}

TimerInterface::TimerInterface() :
	m_impl( new TimerInterfacePrivate() )
{
}

TimerInterface::~TimerInterface()
{
	delete m_impl;
}

Timer&
TimerInterface::createTimer( const string &id )
{
	return m_impl->createTimer( id );
}

Timer&
TimerInterface::timer( const string &id )
{
	return m_impl->timer( id );
}

void
TimerInterface::destroyTimer( const string &id )
{
	m_impl->destroyTimer( id );
}

void
TimerInterface::updateAll() const
{
	m_impl->updateAll();
}

} /* Baukasten */

