#ifndef ENTITIES_SI8O8CQ0
#define ENTITIES_SI8O8CQ0

#include <game_entity.h>
#include <generic_state.h>

using namespace Baukasten::Core;

class Unit : public GameEntity {
public:
	Unit( const std::string& );
	virtual ~Unit();

	std::string getName() const;
	int getHP() const;
	int getMP() const;
	int getLevel() const;
	int getExperience() const;
	int getSex() const;

private:
	StateString*	mName;
	StateInt*		mHP;
	StateInt*		mMP;
	StateInt*		mLevel;
	StateInt*		mExperience;

	Action*			mAddExpAction;
	Action*			mLevelUpAction;
	Action*			mHitAction;
	Action*			mDieAction;
	Action*			mLuaAction;
};

#endif /* end of include guard: ENTITIES_SI8O8CQ0 */

