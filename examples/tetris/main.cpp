#include "game.h"

int main(int argc, char *argv[])
{
	Game game( "Tetris", argc, argv );
	game.start();
	return 0;
}
