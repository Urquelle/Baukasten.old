#include "game.h"
#include "logical_space.h"
#include "virtual_space.h"

using namespace Eisenfaust;

Game::Game()
{
    m_lSpace = std::shared_ptr<LogicalSpace>( new LogicalSpace );
    m_vSpace = std::shared_ptr<VirtualSpace>( new VirtualSpace );
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

