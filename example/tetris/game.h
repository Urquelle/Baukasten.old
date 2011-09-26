#ifndef GAME_QC1L8Y4Z
#define GAME_QC1L8Y4Z

#include <game_entity.h>

namespace Baukasten {
	class IInput;
	class IGraphics;
} /* Baukasten */

class Game : public Baukasten::GameEntity {
public:
	Game ( const string& );
	virtual ~Game();

	void start();

protected:
	void init();
	void run();

private:
	Baukasten::IInput*		mInput;
	Baukasten::IGraphics*	mGraphics;
};

#endif /* end of include guard: GAME_QC1L8Y4Z */

