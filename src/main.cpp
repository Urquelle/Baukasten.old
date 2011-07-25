#include "game.h"

int main(int argc, const char *argv[])
{
    using namespace Eisenfaust;

    Game &game = Game::instance();

    game.start();
    game.pause();
    game.stop();

    return 0;
}

