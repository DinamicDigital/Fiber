#pragma once
#include "../FiberDLL.h"

typedef enum _LogLayer
{
	Good, Info, Warn, Error
} LogLayer;

void FIBER_API log_message(LogLayer log_layer, const char* message, ...);
void log_message(LogLayer log_layer, const char* message, ...);