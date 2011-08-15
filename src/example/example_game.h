#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <game.h>

class ExampleGame : public Baukasten::Core::Game
{
public:
    ExampleGame();
    virtual ~ExampleGame();

    void start();
    void pause();
    void stop();
};

#endif /* end of include guard: GAME_QESA072Y */

