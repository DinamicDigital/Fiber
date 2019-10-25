#include "Window.h"
#include "../../Renderer/glad/glad.h"
#include "../../Debugging/Logger.h"
#include <SDL.h>

#include <stdlib.h>
#include <string.h>

// Important Stuff
static SDL_Window* _window = 0;
static SDL_GLContext _mainContext;

// Window Options
static int _fullscreen = 0;


// TODO: make window_err not have to do the following
// window_err: have to add \n%s\n to the end of err_msg for it to work properly
static void window_err(const char* err_msg)
{
	log_message(Error, err_msg, SDL_GetError());
	exit(2); // TODO: Maybe make an error code specification?
}

void window_done()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
	exit(0);
}

void swap_frame_buffers() { SDL_GL_SwapWindow(_window); }

// fullscr(0 = fullscreen disabled, 1 = fullscreen enabled)
void window(const char* title, int width, int height, int fullscr)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		window_err("SDL failed to init video!\n%s\n");

	atexit(window_done);

	SDL_GL_LoadLibrary(0); // 0 = default openGL

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // enable Hardware Acceleration
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_fullscreen = fullscr;

	if (_fullscreen)
	{
		_window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	}
	else {
		_window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_OPENGL);
	}
	if (window == 0) window_err("Could not create window.\n%s\n");

	// OpenGL Context Creation

	_mainContext = SDL_GL_CreateContext(_window);
	if (_mainContext == 0)
		window_err("Could not create OpenGL context.\n%s\n");

	gladLoadGLLoader(SDL_GL_GetProcAddress);

	log_message(Good, "OpenGL loaded");
	log_message(Info, "Vendor:   %s", glGetString(GL_VENDOR));
	log_message(Info, "Renderer: %s", glGetString(GL_RENDERER));
	log_message(Info, "Version:  %s", glGetString(GL_VERSION));

	// Enable VSync
	SDL_GL_SetSwapInterval(1);

	// not yet using depth testing and face culling so temporarily disable them.
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	int w, h;
	SDL_GetWindowSize(_window, &w, &h);
	glViewport(0, 0, w, h);


}

static SDL_Event e;

void handle_events()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) window_done();
	}
}