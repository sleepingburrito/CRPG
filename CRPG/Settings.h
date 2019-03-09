#pragma once
#include <SDL.h>
#include <stdbool.h>
#include <SDL_image.h>


#define VERSION_NUMBER 1
#define SCREEN_WIDTH 640
#define SCREEN_WIDTH_HALF ( SCREEN_WIDTH / 2 )
#define SCREEN_HEIGHT 360
#define SCREEN_HEIGHT_HALF ( SCREEN_HEIGHT / 2 )
#define WINDOW_TITLE "CRPG test"
Uint32 WINDOW_SETTINGS = SDL_RENDERER_ACCELERATED;// | SDL_RENDERER_PRESENTVSYNC;
#define SDL_SCALE "0" // 0 is nearest neighbor


//audio settings
#define AUDIO_SAMPLE_RATE 44100
#define AUDIO_SAMPLE_SIZE 1024
#define AUDIO_CHANNELS_COUNT 2


//image loading settings
#define MASTER_IMAGE_FORMAT IMG_INIT_PNG


//ErrorMessages.h
#define ERROR_MSG_STR "\nError file: %s\nFunction: %s\nLine: %llu\nPreprocessor date: %s\nPreprocessor time: %s\nVersion Number: %u\nSDL Error: %s"


//file
#define FILE_FOLDER "\\"
#define RESOURCES_FOLDER "resources" FILE_FOLDER
#define IMAGE_FOLDER RESOURCES_FOLDER "images" FILE_FOLDER
#define MAPDATA_FOLDER RESOURCES_FOLDER "mapdata" FILE_FOLDER


//car
#define CARS_COUNT_MAX 100 //max cars you can have in game at one time

#define CAR_PHYSICS_DRIFT_TURN_ACTIVATION_MIN 0.0001
#define CAR_PHYSICS_TIMESTEP_MS 16
#define CAR_PHYSICS_NO_DRIFT 1.0

#define CAR_WALL_SPEED_DECAY 0.9 //how much speed you loose from hitting the wall
#define CAR_COLLIDE_SPEED_TRANSFER 2.0 //other car gets half the speed
#define CAR_WALL_SEARCH_ACCURACY 0.15

bool noClip = false;


//GraphicsQueue.h
#define GRAPHICS_QUEUE_COUNT_MAX 1000
#define GRAPHICS_MASK_DISTANCE 500 //how far outside the window you can draw till culling


//map settings
#define MAP_NOTILE -1

#define CAMERA_START_X 0
#define CAMERA_START_Y 0

#define	CHASE_CAM_MAX_DISTANCE 230.0
#define CASE_CAM_SPEED_SCALE 2.5

#define MAP_WIDTH_IN_TILES 300
#define MAP_HEIGHT_IN_TILES 300
#define MAP_SIZE_MAX_IN_TILES ( MAP_WIDTH_IN_TILES * MAP_HEIGHT_IN_TILES )

#define TILE_SIZE_PIXELS 32
#define TILE_SIZE_MAX_PIXELS ( TILE_SIZE_PIXELS * TILE_SIZE_PIXELS )

#define MAP_WIDTH_IN_PIXELS ( TILE_SIZE_PIXELS * MAP_WIDTH_IN_TILES )
#define MAP_HEIGHT_IN_PIXELS ( TILE_SIZE_PIXELS * MAP_HEIGHT_IN_TILES )

#define SCREEN_WIDTH_IN_TILES (int32_t)( SCREEN_WIDTH / TILE_SIZE_PIXELS )
#define SCREEN_HEIGHT_IN_TILES (int32_t)( SCREEN_HEIGHT / TILE_SIZE_PIXELS )


//map file settings
#define MAP_TILESET_FILE IMAGE_FOLDER"testTiles.png"
#define MAP_FILE_TILEDATA_BACKGROUND MAPDATA_FOLDER "back-layer.txt"
#define MAP_FILE_TILEDATA_MIDDELGROUND MAPDATA_FOLDER "mid-layer.txt"
#define MAP_FILE_TILEDATA_FOREGROUND MAPDATA_FOLDER "top-layer.txt"
#define MAP_FILE_TILEDATA MAPDATA_FOLDER "tile-data.txt"

#define MAP_FILE_LOAD_NO_ANIMATION -1


//XML settings
#define XML_TAG_STRING_COUNT_MAX 16
#define XML_NUMBER_BUFFER_SIZE 12
#define XML_TAG_COUNT_MAX 1000