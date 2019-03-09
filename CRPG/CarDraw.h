#pragma once
#include <math.h>
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "CarsDataType.h"
#include "CarManager.h"
#include "MathEx.h"
#include "SDLtimingTools.h"
#include "Settings.h"
#include "CarDatabase.h"
#include "GraphicsQueue.h"

void DrawCars( void )
{
	//for testing draw all cars in the center of the screen

	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
	{
		if ( i_cars[i].active == false )
			continue;

		i_carSprites[i_cars->carType].x = (int32_t)i_cars[i].x;
		i_carSprites[i_cars->carType].y = (int32_t)i_cars[i].y;
		i_carSprites[i_cars->carType].angle = i_cars[i].angle + HALF_PI;;
		i_carSprites[i_cars->carType].depth = DEPTH_MIDDELGROUND;

		AddSpriteGraphicsQueue( i_carSprites[i_cars->carType] );
	}
}