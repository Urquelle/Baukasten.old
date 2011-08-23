#ifndef INC_ACTIONS_GW487EFJ
#define INC_ACTIONS_GW487EFJ

#include "global.h"
#include "abstract_manager.h"

namespace Baukasten {
	class Action;

	class BAUKASTEN_EXPORT ActionsManager : public AbstractManager<Action> {
	public:
		ActionsManager();
		virtual ~ActionsManager();

		void addAction( Action* );
		void addAction( const std::string&, Action* );
		Action* getAction( const std::string& ) const;
		ActionMap getActions() const;
		bool hasAction( const std::string& ) const;

		void invokeAction( const std::string& );
		void invokeAction( const std::string&, GameEntity* );
		void invokeAction( const std::string&, GameEntityList );

		void dropAction( const std::string& );

		void runActions();

	private:
		ActionList	mActionQueue;
	};
} /* Baukasten */

#endif /* end of include guard: INC_ACTIONS_GW487EFJ */