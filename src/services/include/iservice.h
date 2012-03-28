#pragma once

#include "services/Global"

namespace Baukasten {
	class Services;

	class IService {
	public:
		IService( const string &name ) :
			m_ready( false ),
			m_name( name )
		{
		}

		virtual void init( Services *services ) = 0;
		virtual void setIsReady( bool ready ) { m_ready = ready; }
		virtual bool isReady() const { return m_ready; }
		virtual string name() const { return m_name; }

	private:
		bool m_ready;
		string m_name;
	};
}

