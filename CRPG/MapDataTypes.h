#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "Settings.h"
#include "GraphicsDataType.h"


//camera
double i_camX = CAMERA_START_X;
double i_camY = CAMERA_START_Y;


//map data
enum tileDepths
{
	TILE_DEPTHS_BACKGROUND,
	TILE_DEPTHS_MIDDLEGROUNDTILE,
	TILE_DEPTHS_FOREGROUND,
	TILE_DEPTHS_GROUND_COUNT_MAX
};

const int32_t tileDepthMap[TILE_DEPTHS_GROUND_COUNT_MAX] = 
{
	DEPTH_BACKGROUND,
	DEPTH_BACKGROUND_TOP,
	DEPTH_FOREGROUND
};

typedef struct 
{
	int32_t spriteTileGraphicsIndex;
	int32_t frames;
	int32_t delay;
}spriteTileGraphic;

typedef struct
{
	spriteTileGraphic spriteTileGraphicsIndex[TILE_DEPTHS_GROUND_COUNT_MAX];
	bool solid;
} MapElement;

MapElement * i_mapData = NULL;


//tile graphics data
sprite * i_tileGraphics = NULL;
size_t i_tileGraphicsCount = 0;


void DumpMapDataFile()
{

}