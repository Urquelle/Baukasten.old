#pragma once

#include "core/Global"

namespace Baukasten {
	class CoreServices;

	class IServiceInterface {
	public:
		IServiceInterface( const string &name ) :
			m_ready( false ),
			m_name( name )
		{
		}

		virtual void init( CoreServices *services ) = 0;
		virtual void setIsReady( bool ready ) { m_ready = ready; }
		virtual bool isReady() const { return m_ready; }
		virtual string serviceName() const { return m_name; }

	private:
		bool m_ready;
		string m_name;
	};
}

