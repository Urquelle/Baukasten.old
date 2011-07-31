#include "game.h"

int main(int argc, const char *argv[])
{
    using namespace Eisenfaust;

    Game game;

    game.start();
    game.pause();
    game.stop();

    return 0;
}

