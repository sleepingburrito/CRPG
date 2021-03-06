//STD
#include <stdlib.h>

//SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

//mine
#include "SDLStartWindow.h"
#include "SDLtimingTools.h"
#include "MathEx.h"
#include "FileBin.h"
#include "SDLLoadingTileSet.h"
#include "StringTools.h"
#include "CarDatabase.h"
#include "SDLKeys.h"
#include "CarPhysics.h"
#include "CarManager.h"
#include "CarPlayerInteraction.h"
#include "CarDraw.h"
#include "GraphicsDataType.h"
#include "GraphicsQueue.h"
#include "MapDraw.h"
#include "LoadMapFile.h"
#include "FileXMLtools.h"

int main( int ac, char** av )
{
	//mh
	ac = 0;
	av = NULL;

	
	//initiationm, order matters
	StartSDL();
	StartKeys();

	StartGraphicsQueue();
	StartMap();
	LoadMapFiles();

	StartLoadCarData();
	StartCars();
	StartPlayersCar();
	
	//test cars
	SetPlayersCar( CTI_TEST_CAR, -200, -200 );

	car * ccar = NextInactiveCar(); //test car to collied into
	*ccar = GetCarData( CTI_TEST_CAR );
	ccar->x = 300;
	ccar->y = 200;


	//fps
	UpdateAllTimeTools();
	timers fpsTimerDist = TimerSet( ONE_SECOND_MS );




	//main loop
	SDL_Event event;
	while( ir_keys[KEY_EXIT] == KEY_STATE_UP )
	{
		//==update keys==
		SDL_PollEvent( &event );
		UpdateKeysStep();

		//==step event==
		PlayersCarStep();
		CarPhysicsStep();


		//==drawing==
		//clearing the buffer
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
		SDL_RenderClear( renderer );

		//move camera
		CaseCam( i_cars[0].x + (i_cars[0].width / 2.0) , i_cars[0].y + (i_cars[0].height / 2.0), i_cars[0].angle, i_cars[0].speed );

		//drawing
		DrawCars();
		DrawMap();
		DrawGraphicsQueue();		

		//sdl drawing
		SDL_RenderPresent( renderer );


		//draw fps
		UpdateAllTimeTools();
		if ( TimerPassed( fpsTimerDist ) )
		{
			fpsTimerDist = TimerSet( ONE_SECOND_MS );
			SDL_Log( "fps: %d dt: %d\n", (int)fps, (int)deltaTime );
		}
	}

	ShutdownSDL();
    return EXIT_SUCCESS;
}

