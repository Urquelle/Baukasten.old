#ifndef GAME_QC1L8Y4Z
#define GAME_QC1L8Y4Z

#include "input/InputInterface"

namespace Baukasten {
    class GameEntity;
	class IInput;
	class IGraphics;
	class IAudio;
} /* Baukasten */

class Game {
public:
	Game ( const std::string&, int, char** );
	virtual ~Game();

	void start();

	void onKeyDown( Baukasten::Key, Baukasten::Modifier );

protected:
	void init();
	void run();

private:
    Baukasten::GameEntity*  m_game;
	Baukasten::IAudio*		m_audio;
	Baukasten::IGraphics*	m_graphics;
	Baukasten::IInput*		m_input;
	int m_argc;
	char** m_argv;
};

#endif /* end of include guard: GAME_QC1L8Y4Z */

