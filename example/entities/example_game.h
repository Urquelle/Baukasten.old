#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game_entity.h>

#include <string>

class WorldMap;

namespace Ogre {
	class Root;
	class SceneManager;
} /* Ogre */

class ExampleGame : public Baukasten::GameEntity
{
public:
	ExampleGame( const std::string &id );
	virtual ~ExampleGame();

	void start();
	bool keepRunning() const;

protected:
	void run();
	int init();

private:
	WorldMap*			mWorldMap;

	Ogre::Root*			mRoot;
	Ogre::SceneManager*	mSceneManager;
};

#endif /* end of include guard: GAME_QESA072Y */

