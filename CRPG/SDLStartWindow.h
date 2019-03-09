#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Settings.h"
#include "ErrorMessages.h"

SDL_Window   * window   = NULL;
SDL_Renderer * renderer = NULL;
SDL_Surface  * surface  = NULL;
Uint8        * keyState = NULL;

void StartSDL( void )
{
	if(
		   0 == SDL_Init( SDL_INIT_EVERYTHING )
		&& NULL != ( window   = SDL_CreateWindow( WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 ) )
		&& NULL != ( renderer = SDL_CreateRenderer( window, -1, WINDOW_SETTINGS ) )
		&& SDL_TRUE == ( SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, SDL_SCALE ) )
		&& MASTER_IMAGE_FORMAT == IMG_Init( MASTER_IMAGE_FORMAT )
		&& -1 != Mix_OpenAudio( AUDIO_SAMPLE_RATE, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS_COUNT, AUDIO_SAMPLE_SIZE )
	  )
		keyState = (Uint8*)SDL_GetKeyboardState(NULL);
	else
		LogError( __FILE__, __func__, __LINE__ );
}

void ShutdownSDL( void )
{
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}