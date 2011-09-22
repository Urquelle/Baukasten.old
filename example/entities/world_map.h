#ifndef WORLD_MAP_Z9CGYC5U
#define WORLD_MAP_Z9CGYC5U

#include <game_entity.h>
#include <input_interface.h>

class WorldMap : public Baukasten::GameEntity {
public:
	WorldMap( const std::string& );
	virtual ~WorldMap();

	void onKeyDown( Baukasten::Key, Baukasten::Modifier );
	void onKeyUp( Baukasten::Key, Baukasten::Modifier );

private:
	bool mMoveLeft;
	bool mMoveRight;
	bool mMoveUp;
	bool mMoveDown;
};

#endif /* end of include guard: WORLD_MAP_Z9CGYC5U */
