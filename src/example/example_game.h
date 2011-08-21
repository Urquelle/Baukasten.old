#ifndef GAME_QESA072Y
#define GAME_QESA072Y

#include <string>

class ExampleGame
{
public:
    ExampleGame();
    virtual ~ExampleGame();

    void start();
    void pause();
    void stop();

protected:
    void run();
    void processUserInput();
    void renderScene();

    void initRenderingSystem();
    void initScene( const std::string& );

    bool mKeepRunning;
};

#endif /* end of include guard: GAME_QESA072Y */

