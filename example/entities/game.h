#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>
#include <input_interface.h>

#include <string>

class WorldMap;

namespace Baukasten {
	class OgreInterface;
	class IInput;
}

class Game : public Baukasten::GameEntity
{
public:
	Game( const std::string& );
	virtual ~Game();

	void start();
	bool keepRunning();
	void onKeyDown( Baukasten::Key, Baukasten::Modifier );

protected:
	void run();
	int init();

private:
	WorldMap*				mWorldMap;
	Baukasten::OgreInterface*	mGraphics;
	Baukasten::IInput*		mInput;
};

#endif /* end of include guard: GAME_QESA072Y */

