#include "game.h"

using namespace Eisenfaust;

Game* Game::m_instance = 0;

Game& Game::instance()
{
    if ( m_instance == 0 )
        m_instance = new Game();
    return *m_instance;
}

Game::Game()
{
    //
}

Game::~Game()
{
    //
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
