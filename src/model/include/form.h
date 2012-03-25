#ifndef FORM_H
#define FORM_H

#include "model/Drawable"
#include "model/EntityManager"
#include "model/Global"
#include "model/StateManager"

#include <string>

namespace Baukasten {
	class LogicalSpace;
	class VirtualSpace;
	class IGraphics;

	class BAUKASTEN_EXPORT Form : public Drawable,
	public EntityManager, public StateManager {
	public:
		Form( const string&, IGraphics *graphics = 0 );
		virtual ~Form();

		void addToLSpace( GameEntity* );
		void addToLSpace( const string&, GameEntity* );
		void removeFromLSpace( const string& );
		LogicalSpace* lSpace() const;

		void addToVSpace( Form* );
		void addToVSpace( const string&, Form* );
		void removeFromVSpace( const string& );
		VirtualSpace* vSpace() const;

		virtual void constructScene();
		virtual void render();

	protected:
		IGraphics *graphics() const;

	private:
		shared_ptr<LogicalSpace> m_lSpace;
		shared_ptr<VirtualSpace> m_vSpace;
		IGraphics *m_graphics;
	};
}

#endif // FORM_H

