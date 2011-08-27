#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>

#include <string>

class WorldMap;

namespace Baukasten {
	class IGraphics;
}

class ExampleGame : public Baukasten::GameEntity
{
public:
	ExampleGame( const std::string& );
	virtual ~ExampleGame();

	void start();
	bool keepRunning() const;

protected:
	void run();
	int init();

private:
	WorldMap*				mWorldMap;
	Baukasten::IGraphics*	mGraphics;
};

#endif /* end of include guard: GAME_QESA072Y */

