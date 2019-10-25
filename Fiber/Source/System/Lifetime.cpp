#include "Lifetime.h"
#include "Windowing/Window.h"
#include "..//Renderer/Renderer.h"
#include <stdint.h>

void run(const char* title, int w, int h, int fullscreen)
{
	uint8_t running = 1;
	// TODO: add config file exposed to user to make windowing simpler for the user.
	window("Why!", w, h, fullscreen);
	render_init();
	while (running)
	{
		render();
		handle_events();
		swap_frame_buffers();
	}
	
	window_done();
	
}