#include <SDL/SDL.h>

#include <iostream>

#include "common.h"
#include "application.h"

using namespace omok::logging;

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
	bool exit = false;
	omok::ApplicationSP app = std::make_shared<omok::Application>();

	if (!app->init())
	{
		exit = true;
	}

	// program running
	if(!exit)
		app->run();

	// program terminating

	app->clean();

	// close logfile
	if (logger.has(logfile))
	{
		logger.remove(logfile);
	}
	fclose(logfile);


	return 0;
}





