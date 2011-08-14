#include "game.h"
#include "logical_space.h"
#include "virtual_space.h"

using namespace Eisenfaust::Core;

Game::Game() :
    mLogicalSpace( std::shared_ptr<LogicalSpace>( new LogicalSpace ) ),
    mVirtualSpace( std::shared_ptr<VirtualSpace>( new VirtualSpace ) )
{
}

Game::~Game()
{
}

void Game::start()
{
}

void Game::pause()
{
}

void Game::stop()
{
}

