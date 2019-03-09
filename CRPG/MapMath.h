#pragma once
#include <stdbool.h>

#include "Settings.h"


bool OutsideMap( int32_t xtest, int32_t ytest )
{
	return xtest < 0 || ytest < 0 || xtest >= MAP_WIDTH_IN_TILES || ytest >= MAP_HEIGHT_IN_TILES;
}

size_t CoordinatesToMapIndex( size_t x, size_t y )
{
	return y * MAP_WIDTH_IN_TILES + x;
}

