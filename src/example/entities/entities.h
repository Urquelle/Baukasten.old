#ifndef ENTITIES_SI8O8CQ0
#define ENTITIES_SI8O8CQ0

#include <form.h>
#include <game_entity.h>
#include <generic_state.h>

using namespace Baukasten;

class Unit : public GameEntity {
public:
	Unit( const std::string& );
	virtual ~Unit();

	std::string getName() const;
	void setName( const std::string& );

	int getHP() const;
	int getMP() const;
	int getLevel() const;
	int getExperience() const;
	int getSex() const;
};

#endif /* end of include guard: ENTITIES_SI8O8CQ0 */

