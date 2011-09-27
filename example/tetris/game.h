#ifndef GAME_QC1L8Y4Z
#define GAME_QC1L8Y4Z

#include <game_entity.h>
#include <input_interface.h>

namespace Baukasten {
	class IInput;
	class IGraphics;
} /* Baukasten */

class Game : public Baukasten::GameEntity {
public:
	Game ( const string& );
	virtual ~Game();

	void start();

	void onKeyDown( Baukasten::Key, Baukasten::Modifier );

protected:
	void init();
	void run();

private:
	Baukasten::IInput*		mInput;
	Baukasten::IGraphics*	mGraphics;
};

#endif /* end of include guard: GAME_QC1L8Y4Z */

