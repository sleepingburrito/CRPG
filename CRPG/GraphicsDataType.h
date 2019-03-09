#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "SDLLoadingTileset.h"

enum StandertDepths
{
	DEPTH_DEBUG,
	DEPTH_UI_TOP,
	DEPTH_UI,
	DEPTH_FOREGROUND_TOP,
	DEPTH_FOREGROUND,
	DEPTH_MIDDELGROUND_TOP,
	DEPTH_MIDDELGROUND,
	DEPTH_BACKGROUND_TOP,
	DEPTH_BACKGROUND,
	DEPTH_COUNT_MAX
};

enum Spaces
{
	WORLD_SPACE, //moved by camera
	SCREEN_SPACE //coordinates are used raw
};

typedef struct
{
	int32_t x;
	int32_t y;
	int32_t depth; //smaller draws on top
	int32_t workingSpace;

	tileset tiles;
	size_t startingTile;

	int32_t delay; //in ms between frames
	size_t tileState; //internal use
	size_t lengthTile;

	double angle;
} sprite;

sprite SafeDefaultsSprite( tileset tiles )
{
	sprite ts;

	
	ts.x = 0;
	ts.y = 0;
	ts.depth = 0;
	ts.workingSpace = WORLD_SPACE;

	ts.tiles = tiles;
	ts.startingTile = 0;

	ts.delay = 0;
	ts.tileState = 0;
	ts.lengthTile = 1;

	ts.angle = 0.0;

	return ts;
}