#pragma once
#include <SDL.h>
#include <stdint.h>

//pubic members
typedef uint32_t timers;
timers deltaTime = 0; //how long last frame took
#define ONE_SECOND_MS 1000

//needs to be called eatch frame to be updated
void UpdateDeltaTimeAndMasterClock( void )
{
	static timers timeLastFrame = 0;

	//todo: error out on rollover for now
	if ( timeLastFrame > SDL_GetTicks() )
		LogError( __FILE__, __func__, __LINE__ );

	//find out how much time has passed on timer since last update
	deltaTime = SDL_GetTicks() - timeLastFrame;

	//reset delta time finder
	timeLastFrame = SDL_GetTicks();
}


//timer tools
timers TimerSet( timers time )
{
	return SDL_GetTicks() + time;
}

timers TimerPassed( timers timer )
{
	return timer < SDL_GetTicks();
}


//fps tools
size_t fps = 0;
void UpdateFpsTimer( void )
{
	static size_t fpsCounter = 0;
	static timers fpsTimer = 0;

	++fpsCounter;
	if ( TimerPassed( fpsTimer ) )
	{
		fpsTimer = TimerSet( ONE_SECOND_MS );
		fps = fpsCounter;
		fpsCounter = 0;
	}
}


//updating time tools
void UpdateAllTimeTools( void )
{

	UpdateDeltaTimeAndMasterClock();
	UpdateFpsTimer();
	
}