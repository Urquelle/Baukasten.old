#include "game.h"
#include "logical_space.h"
#include "virtual_space.h"

using namespace Baukasten::Core;

Game::Game() :
    mLogicalSpace( std::shared_ptr<LogicalSpace>( new LogicalSpace ) ),
    mVirtualSpace( std::shared_ptr<VirtualSpace>( new VirtualSpace ) )
{
}

Game::~Game()
{
}
