#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>

#include <SDL/SDL.h>

#include <string>

class WorldMap;

namespace Baukasten {
	class IGraphics;
	class InputInterface;
}

class Game : public Baukasten::GameEntity
{
public:
	Game( const std::string& );
	virtual ~Game();

	void start();
	bool keepRunning();
	void onKeyDown( SDLKey, SDLMod );

protected:
	void run();
	int init();

private:
	WorldMap*						mWorldMap;
	Baukasten::IGraphics*			mGraphics;
	Baukasten::InputInterface*		mInput;
};

#endif /* end of include guard: GAME_QESA072Y */

