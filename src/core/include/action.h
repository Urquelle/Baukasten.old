#ifndef ACTION_4GNSEOOP
#define ACTION_4GNSEOOP

#include "global.h"
#include "entity.h"

#include <string>
#include <list>

namespace Baukasten {
	class GameEntity;

	class BAUKASTEN_EXPORT Action : public Entity {
	public:
		Action( GameEntity&, const std::string& );
		virtual ~Action();

		GameEntity* getSource() const;
		void clear();
		bool isActive() const;
		void setActive( bool );

		void setTarget( GameEntity* );
		GameEntity* getTarget();

		void setTargets( GameEntityList& );
		GameEntityList getTargets();

		virtual bool done() const;
		virtual void run();
		virtual void doAction( GameEntity* ) = 0;

	private:
		GameEntity*		mSource;
		GameEntity*		mTarget;
		GameEntityList	mTargets;
		bool			mActive;
	};
} /* Baukasten */

#endif /* end of include guard: ACTION_4GNSEOOP */
