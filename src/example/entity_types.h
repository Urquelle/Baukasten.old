#ifndef ENTITY_TYPES_QYICYEIC
#define ENTITY_TYPES_QYICYEIC

#include <entity_type.h>
#include <generic_state.h>

using namespace Baukasten::Core;

class BasicClass : public EntityType {
public:
	BasicClass( const std::string& );
	virtual ~BasicClass();

private:
	StateInt*	mSex;
	StateInt*	mMovement;
	StateInt*	mJumpHeight;
	StateInt*	mSpeed;
};

#endif /* end of include guard: ENTITY_TYPES_QYICYEIC */
