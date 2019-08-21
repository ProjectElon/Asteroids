#include "Game.h"

int main(int argc, char *argv[])
{	
	
	astro::Game game;
	game.Init();
	game.Run();
	game.Free();

	return 0;
}