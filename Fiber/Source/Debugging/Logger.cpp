#include "Logger.h"
#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

typedef enum Colors
{
	Black, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkMagenta, DarkYellow, LightGrey, Grey,
	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, LightYellow, White
};

static void _set_console_color(int foreground_color, int background_color)
{
	// make both colors 4 bits and shift background to high bits.
	WORD color = ((background_color & 0x0F) << 4) | (foreground_color & 0x0F);
	SetConsoleTextAttribute(hConsole, color);
}

void log_message(LogLayer log_layer, const char* message, ...)
{
	va_list args;
	va_start(args, message);
	switch (log_layer)
	{
	case Good:
		_set_console_color(LightGreen, Black);
		vfprintf(stdout, message, args);
		va_end(args);
		printf("\n");
		break;
	case Info:
		_set_console_color(DarkYellow, Black);
		vfprintf(stdout, message, args);
		va_end(args);
		printf("\n");
		break;
	case Warn:
		_set_console_color(LightYellow, Black);
		vfprintf(stdout, message, args);
		va_end(args);
		printf("\n");
		break;
	case Error:
		_set_console_color(LightRed, Black);
		vfprintf(stderr, message, args);
		va_end(args);
		printf("\n");
		break;
	default:
		_set_console_color(White, Black);
		vfprintf(stdout, message, args);
		va_end(args);
		printf("\n");
		break;
	}
	va_end(args);
}