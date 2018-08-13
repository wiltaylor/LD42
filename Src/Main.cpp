#include "Game.h"
#ifndef __linux__
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Game* game;

#ifdef __EMSCRIPTEN__
void webLoop()
{
	game->runLoop();
}
#endif

int main(int argc, char *argv[])
{
	std::cout << "Before main game" << std::endl;

	std::cout << SDL_GetBasePath() << std::endl;

	game = new Game;


#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(webLoop, 0, 1);

	std::cout << "set main loop" << std::endl;
#else

	while (game->isRunning())
	{
		game->runLoop();
	}

	delete game;
#endif

  return 0;
}

