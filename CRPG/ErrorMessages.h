#pragma once
#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "Settings.h"


__declspec(noreturn) void LogError( const char * const filename, const char * const functionName, const uint64_t lineNumber )
{
	//try and get it out to the console
	SDL_LogCritical( SDL_LOG_CATEGORY_ERROR, ERROR_MSG_STR, filename, functionName, lineNumber, __DATE__, __TIME__, VERSION_NUMBER, SDL_GetError() );

	//DEBUG: pause to see error, remove later
	system("pause");

	//close everything
	exit( EXIT_FAILURE );
}