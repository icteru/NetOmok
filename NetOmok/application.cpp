#include "application.h"

#include <SDL/SDL.h>

#include <GL/glew.h>
#include <Gl/GL.h>

#include "common.h"

#include <vector>

using namespace omok::logging;

bool SDL_Initialized = false;

int initSDL()
{
	if (SDL_Initialized)
		return 0;

	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0)
	{
		logger.e("SDL_Init : %s", SDL_GetError());

		return 1;
	}

	// init GL

	// use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// opengl 4.0
	const int major_target = 4;
	const int minor_target = 0;
	int major, minor;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major_target);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor_target);

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	if (major < major_target)
	{
		logger.e("GL_MAJOR_VERSION : Version not support : %d", major);
		logger.e("OpenGL version needs : %d.%d", major_target, minor_target);

		return 2;
	}

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	if (major == major_target && minor < minor_target)
	{
		logger.e("GL_MINOR_VERSION : Version not support : %d", minor);
		logger.e("OpenGL version needs : %d.%d", major_target, minor_target);

		return 2;
	}
	
	// double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// zbuffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	// enable vsync
	SDL_GL_SetSwapInterval(1);

	SDL_Initialized = true;
	return 0;
}

int initGLEW()
{
	// init glew
	GLenum ret;
	glewExperimental = GL_TRUE;
	ret = glewInit();

	if (GLEW_OK != ret) {
		logger.e("glewInit :%s", glewGetErrorString(ret));

		return 3;
	}

	return 0;
}

int quitSDL()
{
	SDL_Quit();

	return 0;
}


int app_count = 0;

omok::Application::Application()
	: exit(false), system_inited(false)
{
	int ret = initSDL();
	if (ret == 0)
	{
		system_inited = true;
		app_count++;
	}
	else
	{
		exit = true;
	}
}

omok::Application::~Application()
{
	if (system_inited)
	{
		app_count--;
		if (app_count == 0)
		{
			quitSDL();
		}
	}
}

bool omok::Application::init()
{
	if (!system_inited)
	{
		logger.e("App init failed");
		logger.e("App system not inited");

		return false;
	}

	logger.d("App init complete");

	return true;
}

void omok::Application::run()
{
	if (!system_inited)
	{
		logger.e("App system not inited");

		return;
	}

	logger.d("App running");

	// create window

	// create context

	// init glew

	// init shader & gl program

	int loopcount = 0;
	while (!exit)
	{
		// loop
		logger.d("App loop count : %d", loopcount);
		loopcount++;

		if (loopcount > 30)
			quit();
	}

}

void omok::Application::quit()
{
	logger.d("App exit");

	exit = true;
}

void omok::Application::clean()
{
	logger.d("App clean");
}
