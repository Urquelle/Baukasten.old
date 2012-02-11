#ifndef GAME_QC1L8Y4Z
#define GAME_QC1L8Y4Z

#include "input/InputInterface"
#include "model/GameEntity"

namespace Baukasten {
	class IInput;
	class IGraphics;
	class IAudio;
} /* Baukasten */

class Game : public Baukasten::GameEntity {
public:
	Game ( const string&, int, char** );
	virtual ~Game();

	void start();

	void onKeyDown( Baukasten::Key, Baukasten::Modifier );

protected:
	void init();
	void run();

private:
	Baukasten::IAudio*		mAudio;
	Baukasten::IGraphics*	mGraphics;
	Baukasten::IInput*		mInput;
	int mArgc;
	char** mArgv;
};

#endif /* end of include guard: GAME_QC1L8Y4Z */

