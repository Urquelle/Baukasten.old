#ifndef ENTITY_TYPES_QYICYEIC
#define ENTITY_TYPES_QYICYEIC

#include <entity_type.h>
#include <generic_state.h>

using namespace Baukasten::Core;

class SquireClass : public EntityType {
public:
	SquireClass( const std::string& );
	virtual ~SquireClass();

private:
	StateInt*	mSex;
	StateInt*	mMovement;
	StateInt*	mJumpHeight;
	StateInt*	mSpeed;
};

#endif /* end of include guard: ENTITY_TYPES_QYICYEIC */
