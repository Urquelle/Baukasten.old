#include "game.h"
#include "logical_space.h"
#include "virtual_space.h"

using namespace Baukasten::Core;

Game::Game() :
    mLogicalSpace( std::shared_ptr<LogicalSpace>( new LogicalSpace ) ),
    mVirtualSpace( std::shared_ptr<VirtualSpace>( new VirtualSpace ) ),
    mKeepRunning( true )
{
}

Game::~Game()
{
}

void Game::start()
{
    run();
}

void Game::pause()
{
}

void Game::stop()
{
}

void Game::run()
{
    while( mKeepRunning ) {
        processUserInput();
        renderScene();
    }
}

void Game::processUserInput()
{
}

void Game::renderScene()
{
}

