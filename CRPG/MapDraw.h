#pragma once
#include <stdint.h>
#include <stdbool.h>

#include "SDLStartWindow.h"
#include "SDLLoadingTileset.h"
#include "GraphicsDataType.h"
#include "GraphicsQueue.h"
#include "Settings.h"
#include "MapDataTypes.h"
#include "SDLtimingTools.h"
#include "MathEx.h"

tileset i_mapTilset;

void StartMap( void )
{
	//==setup map data==
	if ( NULL == ( i_mapData = calloc( MAP_SIZE_MAX_IN_TILES, sizeof(MapElement) ) ) )
		LogError( __FILE__, __func__, __LINE__ );

	//map data defaults
	for( size_t i = 0; i < MAP_SIZE_MAX_IN_TILES; i++ )
	{
		for( size_t i2 = 0; i2 < TILE_DEPTHS_GROUND_COUNT_MAX; i2++ )
			i_mapData[i].spriteTileGraphicsIndex[i2].spriteTileGraphicsIndex = MAP_NOTILE;

		i_mapData[i].solid = false;
	}


	//==setup tile graphics==
	//load tile set
	i_mapTilset = LoadPngImgTileset( MAP_TILESET_FILE, TILE_SIZE_PIXELS, TILE_SIZE_PIXELS );

	//allocate memory for one sprite per tile(on tile sheet)
	i_tileGraphicsCount = i_mapTilset.countMax;

	if ( NULL == ( i_tileGraphics = calloc( i_tileGraphicsCount, sizeof(sprite) ) ) )
		LogError( __FILE__, __func__, __LINE__ );

	//set default sprite data
	for( size_t i = 0; i < i_tileGraphicsCount; i++ )
	{
		i_tileGraphics[i] = SafeDefaultsSprite( i_mapTilset );
		i_tileGraphics[i].startingTile = i;
	}
}


void CaseCam( double x, double y, double angle, double speed )
{
	double distance = ClampD( speed * CASE_CAM_SPEED_SCALE, 1.0, CHASE_CAM_MAX_DISTANCE );
	
	i_camX = CosProjection( angle, x - SCREEN_WIDTH_HALF,  distance );
	i_camY = SinProjection( angle, y - SCREEN_HEIGHT_HALF,  distance );
}


void DrawMap( void )
{
	//make offset for smooth scrolling
	const int32_t scrollx = (int32_t)i_camX % TILE_SIZE_PIXELS;
	const int32_t scrolly = (int32_t)i_camY % TILE_SIZE_PIXELS;

	//find tiles to draw
	for( int32_t drawY = -1; drawY <= SCREEN_HEIGHT_IN_TILES + 1; drawY++ ) //-1 and +1 to draw a little off screen (I do the same for x)
	{
		const int32_t searchY = drawY + ( (int32_t)i_camY / TILE_SIZE_PIXELS ); //where to look in tile space

		for( int32_t drawX = -1; drawX <= SCREEN_WIDTH_IN_TILES + 1; drawX++ )
		{
			const int32_t searchX = drawX + ( (int32_t)i_camX / TILE_SIZE_PIXELS );

			//bounds checking in tile space
			if ( OutsideMap( searchX, searchY ) )
				continue;

			//set base sprite attributes for tile sprite
			const size_t index = searchX + searchY * MAP_WIDTH_IN_TILES;

			const int32_t x = drawX * TILE_SIZE_PIXELS - scrollx;
			const int32_t y = drawY * TILE_SIZE_PIXELS - scrolly;
			const int32_t workingSpace = SCREEN_SPACE;
			int32_t tmpSpriteIndex = 0;
			
			for( size_t i2 = 0; i2 < TILE_DEPTHS_GROUND_COUNT_MAX; i2++ ) //draw all tile depths
				if ( ( tmpSpriteIndex = i_mapData[ index ].spriteTileGraphicsIndex[ i2 ].spriteTileGraphicsIndex ) != MAP_NOTILE )
				{
					if ( tmpSpriteIndex >= i_tileGraphicsCount )
						LogError( __FILE__, __func__, __LINE__ );

					//sprite attributes that will be submitted to the sprite queue
					i_tileGraphics[ tmpSpriteIndex ].x = x;
					i_tileGraphics[ tmpSpriteIndex ].y = y;
					i_tileGraphics[ tmpSpriteIndex ].workingSpace = workingSpace;
					i_tileGraphics[ tmpSpriteIndex ].depth = tileDepthMap[i2];

					//animated tiles
					if ( i_mapData[ index ].spriteTileGraphicsIndex[ i2 ].frames != MAP_FILE_LOAD_NO_ANIMATION )
					{
						i_tileGraphics[ tmpSpriteIndex ].lengthTile = i_mapData[ index ].spriteTileGraphicsIndex[ i2 ].frames;
						i_tileGraphics[ tmpSpriteIndex ].delay      = i_mapData[ index ].spriteTileGraphicsIndex[ i2 ].delay;
					}

					AddSpriteGraphicsQueue( i_tileGraphics[ tmpSpriteIndex ] );
				}				
		}
	}
}