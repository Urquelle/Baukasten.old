#include "example_game.h"
#include "entities.h"

#include <iostream>

ExampleGame::ExampleGame() :
    mKeepRunning( true )
{
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
    run();
}

void ExampleGame::pause()
{
    std::cout << "spiel pausieren." << std::endl;
}

void ExampleGame::stop()
{
    std::cout << "spiel stoppen." << std::endl;
}

void ExampleGame::run()
{
    using namespace Baukasten::Core;
    using namespace std;

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	GameEntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();

    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();

    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();

    sanchez->invokeAction( "hit", targets );
    sanchez->runActions();

	sanchez->invokeAction( "hello" );
	sanchez->runActions();
}

