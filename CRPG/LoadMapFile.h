//these functions are tailored to copying and pasting data out of "Tiled" save files. assume first or last tile is not treated correctly

#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include "ErrorMessages.h"
#include "MapDataTypes.h"
#include "MapDraw.h"
#include "FileBin.h"
#include "FileXMLtools.h"

typedef struct
{
	size_t tileId;
	bool solid;
	int32_t frames;
	int32_t delay;
} tmpTileData;

void i_LoadLayer( const char * const fileName , const int32_t layer, const tmpTileData * const TileData, const size_t solidTileIdBufferCount )
{
	//load file from disk
	char * const fileData = NULL;
	const size_t fileSize = LoadFileBin( fileName, (void *)&fileData );
	
	//parse data
	size_t fileDataIndex = 0;

	char numberBuffer[12]; //number up to a billion (int32)
	size_t bufferCount = 0;

	size_t mapDataCount = 0;

	while( fileDataIndex < fileSize )
	{
		//copy number into buffer
		while( bufferCount < sizeof(numberBuffer) - 1 ) //check if buffer is full
		{
			//number filter
			if ( isdigit( fileData[fileDataIndex] ) )
				numberBuffer[ bufferCount++ ] = fileData[fileDataIndex];

			fileDataIndex++;

			//end condition number parsing
			if ( fileData[fileDataIndex] == ',' || fileDataIndex >= fileSize )
				break;
		}

		//string to number and save map data
		if ( mapDataCount + 1 > MAP_SIZE_MAX_IN_TILES )
			LogError( __FILE__, __func__, __LINE__ );
		else
		{
			numberBuffer[ bufferCount ] = 0; //null term
			
			//tiles with id zero or lower are ignored
			int32_t tileIndex = (int32_t)atoi( numberBuffer ) - 1;

			if ( tileIndex < 1 )
				tileIndex = MAP_NOTILE;


			//set defaults
			i_mapData[mapDataCount].spriteTileGraphicsIndex[layer].frames = MAP_FILE_LOAD_NO_ANIMATION;
			i_mapData[mapDataCount].spriteTileGraphicsIndex[layer].delay = 0;


			//check if solid
			for( size_t i = 0; i < solidTileIdBufferCount; i++ )
				if ( TileData[i].tileId == tileIndex )
				{
					i_mapData[mapDataCount].solid = true;
					i_mapData[mapDataCount].spriteTileGraphicsIndex[layer].frames = TileData[i].frames;
					i_mapData[mapDataCount].spriteTileGraphicsIndex[layer].delay = TileData[i].delay;
					break;
				}

			//add the graphic
			i_mapData[mapDataCount++].spriteTileGraphicsIndex[layer].spriteTileGraphicsIndex = tileIndex;
		}

		bufferCount = 0; //reset number buffer
	}


	//end
	free( fileData );
}


size_t i_LoadTileData( const char * const fileName, tmpTileData * TileData )
{
	StartXML();

	size_t tileDataCount = 0;

	ParseXMLAttributeValues( fileName );
	
	while( MoveNextXMLAttribute("id") )
	{
		if ( tileDataCount + 1 >= MAP_SIZE_MAX_IN_TILES )
			LogError( __FILE__, __func__, __LINE__ );

		
		TileData[tileDataCount].tileId = (int32_t)GetXMLValueFromMove();


		if ( CheckNextXMLAttribute( "s" ) ) //s for solid
		{
			MoveNextXMLAttribute( "s" );
			TileData[tileDataCount].solid = (bool)GetXMLValueFromMove();
		}

		if ( CheckNextXMLAttribute( "f" ) ) //f for frame
		{
			MoveNextXMLAttribute( "f" );
			TileData[tileDataCount].frames = (int32_t)GetXMLValueFromMove();

			if ( CheckNextXMLAttribute( "d" ) )
			{
				MoveNextXMLAttribute( "d" );
				TileData[tileDataCount].delay = (int32_t)GetXMLValueFromMove();
			}
			else
				LogError( __FILE__, __func__, __LINE__ );
		}
		else
		{
			TileData[tileDataCount].frames = MAP_FILE_LOAD_NO_ANIMATION;
			TileData[tileDataCount].delay = 0;
		}

		tileDataCount++;
	}

	EndXML();
	return tileDataCount;
}


void LoadMapFiles( void )
{
	//find out what tiles data
	tmpTileData * TileData = NULL;
	if ( ( TileData = (tmpTileData *)calloc( MAP_SIZE_MAX_IN_TILES, sizeof(tmpTileData) ) ) == NULL )
		LogError( __FILE__, __func__, __LINE__ );

	size_t solidTileIdBufferCount = i_LoadTileData( MAP_FILE_TILEDATA, TileData );

	//load tile graphics
	i_LoadLayer( MAP_FILE_TILEDATA_BACKGROUND, TILE_DEPTHS_BACKGROUND, TileData, solidTileIdBufferCount );
	i_LoadLayer( MAP_FILE_TILEDATA_MIDDELGROUND, TILE_DEPTHS_MIDDLEGROUNDTILE, TileData, solidTileIdBufferCount );
	i_LoadLayer( MAP_FILE_TILEDATA_FOREGROUND, TILE_DEPTHS_FOREGROUND, TileData, solidTileIdBufferCount );

	free(TileData);
}