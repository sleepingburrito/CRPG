#pragma once
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "ErrorMessages.h"
#include "CarsDataType.h"
#include "GraphicsDataType.h"
#include "Settings.h"
#include "SDLLoadingTileset.h"

enum CarTypeIds
{
	CTI_TEST_CAR,
	CTI_COUNT_MAX
};


sprite * i_carSprites = NULL;


void StartLoadCarData( void )
{
	//load sprites
	if ( NULL == ( i_carSprites = (sprite *)calloc( CTI_COUNT_MAX , sizeof(sprite) ) ) )
	{
		LogError( __FILE__, __func__, __LINE__ );
		return; //make happy
	}

	i_carSprites[CTI_TEST_CAR] = SafeDefaultsSprite( LoadPngImgTileset( IMAGE_FOLDER "testCar.png", -1, -1 ) );
}


car GetCarData( const size_t carType )
{
	static size_t generateCarId = 0;
	car returnCar;

	//base
	returnCar.carType = carType;
	returnCar.carId = generateCarId++;
	returnCar.active = true;
	

	//states
	returnCar.steeringWheelState = STEERING_WHEEL_CENTER;
	returnCar.brakingReverse = false;
	returnCar.handBrake = false;
	returnCar.throttle = false;

	returnCar.damage = 0.0;
	returnCar.x = 0.0;
	returnCar.y = 0.0;
	returnCar.speed = 0.0;
	returnCar.angle = 0.0;
	returnCar.turnAmount = 0.0;
	returnCar.drift = CAR_PHYSICS_NO_DRIFT;


	//reference
	returnCar.width = i_carSprites[ carType ].tiles.tileWidth;
	returnCar.height = i_carSprites[ carType ].tiles.tileHeight;
	returnCar.collisionDetectionRadius = MinD( returnCar.width, returnCar.height );
	returnCar.halfWidth = returnCar.width / 2.0;
	returnCar.halfHeight = returnCar.height / 2.0;

	switch( carType )
	{
		case CTI_TEST_CAR:

			returnCar.acceleration = 0.35; //speed per step
			returnCar.maxReverseAcceleration = returnCar.acceleration / 2.0;

			returnCar.drag = 0.002;
			returnCar.friction = 0.08;

			returnCar.handbrakeBrakeAmount = 0.35;
			returnCar.breakingForceMax = 0.5;

			returnCar.turnIncrement = 0.0003;
			returnCar.turnLock = 0.005;
			returnCar.turnDecay = 0.80;

			returnCar.turnSpeedMultiplyer = 2.0; //next 3 is how speed effects turining
			returnCar.turnSpeedLimit = 40.0;
			returnCar.turnSpeedDecayBySpeed = 0.001;

			returnCar.driftHandBreakIncrement = 0.1;
			returnCar.driftHandbreakMax = 2.5;
			returnCar.driftDecay = 0.97;
			returnCar.diftAngleOffsetMax = 0.4;

		return returnCar;

		default:
			LogError( __FILE__, __func__, __LINE__ );
	}

}