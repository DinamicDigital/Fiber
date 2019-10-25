#pragma once
#include "../../FiberDLL.h"

void FIBER_API window_done();

void FIBER_API swap_frame_buffers();

void FIBER_API window(const char* title, int width, int height, int fullscr);

void FIBER_API handle_events();
