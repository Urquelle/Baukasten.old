#include "example_game.h"

#include <iostream>

ExampleGame::ExampleGame()
{
}

ExampleGame::~ExampleGame()
{
}

void ExampleGame::start()
{
    std::cout << "spiel starten." << std::endl;
}

void ExampleGame::pause()
{
    std::cout << "spiel pausieren." << std::endl;
}

void ExampleGame::stop()
{
    std::cout << "spiel stoppen." << std::endl;
}

