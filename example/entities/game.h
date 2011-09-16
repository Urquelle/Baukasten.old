#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>
#include <input_interface.h>

#include <string>

class WorldMap;

namespace Baukasten {
	class IGraphics;
	class IInput;
}

class Game : public Baukasten::GameEntity
{
public:
	Game( const std::string& );
	virtual ~Game();

	void start();

	bool keepRunning();
	int currentMode();

	void onKeyDown( Baukasten::Key, Baukasten::Modifier );

protected:
	void run();
	int init();

private:
	WorldMap*				mWorldMap;
	Baukasten::IGraphics*	mGraphics;
	Baukasten::IInput*		mInput;

	bool mMoveRight;
	bool mMoveLeft;
	bool mMoveUp;
	bool mMoveDown;
};

#endif /* end of include guard: GAME_QESA072Y */

