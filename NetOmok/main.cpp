#include <SDL/SDL.h>

#include <iostream>

#include "common.h"

using namespace omok::logging;

int init()
{
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
	{
		logger.e("SDL_Init : %s", SDL_GetError());

		return 1;
	}


	return 0;
}

int main(int argc, char** argv)
{
	// init logger
	logger.add(stdout);

	// open logfile
	FILE* logfile;
	int err = fopen_s(&logfile, "logfile.txt", "w");
	if (err == 0)
	{
		logger.add(logfile);
	}

	// program start
	logger.i("program start");

	init();

	logger.i("program init complete");





	logger.i("program terminated");

	// close logfile
	if (logger.has(logfile))
	{
		logger.remove(logfile);
	}
	fclose(logfile);


	return 0;
}





