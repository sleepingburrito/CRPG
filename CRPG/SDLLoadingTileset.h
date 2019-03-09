#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdint.h>

#include "SDLStartWindow.h"
#include "MathEx.h"

typedef struct
{
	SDL_Texture * tilesetImage;
	int32_t tileWidth;
	int32_t tileHeight;

	int32_t widthCount;
	int32_t heightCount;

	int32_t countMax;
} tileset;

//less than one with or height will use the whole image as a tile
tileset LoadPngImgTileset( const char * const fileName, const int32_t tileWidth, const int32_t tileHeight )
{
	tileset tmpTiles = { .tilesetImage = NULL, .tileWidth = 0, .tileHeight = 0, .widthCount = 0, .heightCount = 0 };

	//load tile set
	SDL_Surface * tmpImg = IMG_Load( fileName );
	if ( NULL == tmpImg || tmpImg->w < 1 || tmpImg->h < 1 )
	{
		SDL_SetError( IMG_GetError() );
		LogError( __FILE__, __func__, __LINE__ );
	}

	//find size
	if( tileWidth < 1 || tileHeight < 1 ) //using whole image
	{
		tmpTiles.tileWidth = tmpImg->w;
		tmpTiles.widthCount = 1;

		tmpTiles.tileHeight = tmpImg->h;
		tmpTiles.heightCount = 1; 
	}
	else
	{
		tmpTiles.tileWidth = Min( tileWidth, tmpImg->w );
		tmpTiles.tileHeight = Min( tileHeight, tmpImg->h );

		tmpTiles.widthCount =  Max( 1, tmpImg->w / tileWidth );
		tmpTiles.heightCount = Max( 1, tmpImg->h / tileHeight );
	}

	tmpTiles.countMax = tmpTiles.widthCount * tmpTiles.heightCount;

	//make texture
	tmpTiles.tilesetImage = SDL_CreateTextureFromSurface( renderer, tmpImg );
	SDL_FreeSurface( tmpImg );

	if ( NULL == tmpTiles.tilesetImage )
		LogError( __FILE__, __func__, __LINE__ );
	
	return tmpTiles;
}