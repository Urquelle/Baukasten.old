#include "example_game.h"
#include "entities.h"
#include "actions.h"

#include <action.h>
#include <lua/action.h>
#include <generic_state.h>

#include <iostream>

using namespace Baukasten;

ExampleGame::ExampleGame( const std::string &id ) :
	GameEntity( id )
{
	addState( "keepRunning", new StateBool( "keepRunning", true ) );
	addAction( "updateState", new UpdateState( *this ) );
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
	init();
    run();
}

bool ExampleGame::keepRunning() const
{
	return getState<StateBool*>( "keepRunning" )->getValue();
}

void ExampleGame::stop()
{
    std::cout << "spiel stoppen." << std::endl;
}

void ExampleGame::run()
{
    using namespace Baukasten;
    using namespace std;

    Unit *sanchez = new Unit( "sanchez" );
    Unit *gomez = new Unit( "gomez" );
	Unit *ramirez = new Unit( "ramirez" );

	GameEntityList targets;

	targets.push_back( gomez );
	targets.push_back( ramirez );

	while ( keepRunning() ) {
		sanchez->invokeAction( "hit", targets );
		sanchez->runActions();

		invokeAction( "updateState", targets );
		runActions();
	}
}

void ExampleGame::init()
{
}

