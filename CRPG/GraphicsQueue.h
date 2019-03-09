#pragma once
#include <SDL.h>
#include <stdlib.h>
#include "SDLStartWindow.h"
#include "GraphicsDataType.h"
#include "Settings.h"
#include "MapDataTypes.h"

sprite * i_spriteQueue = NULL;
size_t ir_spriteQueueCount = 0;


void StartGraphicsQueue( void )
{
	if ( NULL == ( i_spriteQueue = (sprite *)calloc( GRAPHICS_QUEUE_COUNT_MAX, sizeof(sprite) ) ) )
	{
		LogError( __FILE__, __func__, __LINE__ );
		return; //make happy
	}
}


void AddSpriteGraphicsQueue( sprite inSprite )
{
	if ( inSprite.workingSpace == WORLD_SPACE )
	{
		inSprite.x -= (int32_t)i_camX;
		inSprite.y -= (int32_t)i_camY;

		//culling
		if ( 
					inSprite.x < ( -GRAPHICS_MASK_DISTANCE )
				||  inSprite.x > ( SCREEN_WIDTH + GRAPHICS_MASK_DISTANCE )
				|| 	inSprite.y < ( -GRAPHICS_MASK_DISTANCE )
				||  inSprite.y > ( SCREEN_HEIGHT + GRAPHICS_MASK_DISTANCE )
			)
			return;
	}

	//bounds checking
	if ( ir_spriteQueueCount + 1 > GRAPHICS_QUEUE_COUNT_MAX )
		LogError( __FILE__, __func__, __LINE__ );


	//update animation
	if ( inSprite.lengthTile > 1 && inSprite.delay > 0 )
		inSprite.tileState = inSprite.startingTile + ( SDL_GetTicks() / inSprite.delay ) % inSprite.lengthTile;
	else
		inSprite.tileState = inSprite.startingTile;

	inSprite.tileState = inSprite.tileState % Max( 1, ( inSprite.tiles.countMax - 1 ) );


	//adding
	i_spriteQueue[ ir_spriteQueueCount++ ] = inSprite;
}


void DrawGraphicsQueue( void )
{
	//draw tiles
	for( size_t depthTest = DEPTH_COUNT_MAX - 1; depthTest > 0; depthTest-- )
		for( size_t i = 0; i < ir_spriteQueueCount; i++ )
		{
			if ( i_spriteQueue[i].depth != depthTest )
				continue;


			SDL_Rect tileMapLocation;
			tileMapLocation.x = ( (int32_t)i_spriteQueue[i].tileState % i_spriteQueue[i].tiles.widthCount ) * i_spriteQueue[i].tiles.tileWidth;
			tileMapLocation.y = ( (int32_t)i_spriteQueue[i].tileState / i_spriteQueue[i].tiles.widthCount ) * i_spriteQueue[i].tiles.tileHeight;		
			tileMapLocation.w = i_spriteQueue[i].tiles.tileWidth;
			tileMapLocation.h = i_spriteQueue[i].tiles.tileHeight;
		

			SDL_Rect screenLocation;
			screenLocation.x = i_spriteQueue[i].x;
			screenLocation.y = i_spriteQueue[i].y;
			screenLocation.w = i_spriteQueue[i].tiles.tileWidth;
			screenLocation.h = i_spriteQueue[i].tiles.tileHeight;

			//draw sprites
			SDL_RenderCopyEx
			( 
				renderer,
				i_spriteQueue[i].tiles.tilesetImage,
				&tileMapLocation, 
				&screenLocation, 
				RadiansToDegrees( i_spriteQueue[i].angle ),
				NULL,  
				SDL_FLIP_NONE 
			);



			//////test
			SDL_SetRenderDrawColor( renderer, 255, 0, 0, 0 );

			if ( i_spriteQueue[i].angle > 0 )
			{
				double tmpPoints[4][2];

				double wh = (double)i_spriteQueue[i].tiles.tileWidth / 2.0;
				double tmpX = (double)i_spriteQueue[i].x + wh;

				
				double hh = (double)i_spriteQueue[i].tiles.tileHeight / 2.0;
				double tmpy = (double)i_spriteQueue[i].y + hh;


				//top left
				tmpPoints[0][0] = tmpX - wh;
				tmpPoints[0][1] = tmpy - hh;

				//top right
				tmpPoints[1][0] = tmpX + wh;
				tmpPoints[1][1] = tmpy - hh;

				//bottom left
				tmpPoints[2][0] = tmpX - wh;
				tmpPoints[2][1] = tmpy + hh;

				//bottom right
				tmpPoints[3][0] = tmpX + wh;
				tmpPoints[3][1] = tmpy + hh;


				for( int i2 = 0; i2 < 4; i2++ )
				{
					double dist = DistanceD( tmpX, tmpy, tmpPoints[i2][0], tmpPoints[i2][1] );
					double angle = atan2( tmpy - tmpPoints[i2][1], tmpX - tmpPoints[i2][0] ) - i_spriteQueue[i].angle + HALF_PI;

					SDL_RenderDrawPoint( renderer, 
						(int)( tmpX + dist * sin(angle) ), 
						(int)( tmpy + dist * cos(angle) )
					);
				}
			}
			////end test




		}


	//empty queue
	ir_spriteQueueCount = 0;
}