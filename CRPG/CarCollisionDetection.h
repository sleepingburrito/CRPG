#pragma once
#include <stdint.h>
#include <math.h>

#include "CarsDataType.h"
#include "Settings.h"
#include "MathEx.h"
#include "CarManager.h"
#include "MapDataTypes.h"


//circle based

bool i_TestCarCollision( double x, double y, double halfWidth, double halfHeight, double radius )
{
	if ( noClip )
		return false;

	x += halfWidth;
	y += halfHeight;
	
	for( double testAngle = 0.0; testAngle <= TWO_PI; testAngle += CAR_WALL_SEARCH_ACCURACY )
	{
		int32_t xtest = (int32_t)( SinProjection( testAngle, x, radius ) ) / TILE_SIZE_PIXELS;
		int32_t ytest = (int32_t)( CosProjection( testAngle, y, radius ) ) / TILE_SIZE_PIXELS;

		if ( OutsideMap( xtest, ytest ) )
			continue;

		if ( i_mapData[ CoordinatesToMapIndex( xtest, ytest ) ].solid )
			return true;
	}

	return false;
}


car * i_TestCarCollisionWithOtherCars( double x, double y, double radius, size_t id )
{
	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
	{
		if ( i_cars[i].active == false || i_cars[i].carId == id )
			continue;

		if ( DistanceD( i_cars[i].x, i_cars[i].y, x, y ) <= radius + i_cars[i].collisionDetectionRadius )
			return &i_cars[i];
	}

	return NULL;
}


void i_MoveCollidedCar( car * carToMove, double angle, double speed )
{
	//move the other car and make sure they don't run into anything
	double hspeedOtherCar = speed * cos( angle );
	const double signedMoveHspeedOtherCar = copysign( 1.0, hspeedOtherCar );

	double vspeedOtherCar = speed * sin( angle );
	const double signedMoveVspeedOtherCar = copysign( 1.0, vspeedOtherCar );

	bool keepGoingCarCollide = true;
	while( keepGoingCarCollide )
	{
		keepGoingCarCollide = false;

		if ( fabs(hspeedOtherCar) > 1.0  )
		{
			carToMove->x += signedMoveHspeedOtherCar;
			hspeedOtherCar -= signedMoveHspeedOtherCar;
			
			if ( 
			   i_TestCarCollisionWithOtherCars( carToMove->x, carToMove->y, carToMove->collisionDetectionRadius, carToMove->carId ) != NULL
			|| i_TestCarCollision( carToMove->x, carToMove->y, carToMove->halfWidth, carToMove->halfHeight, carToMove->collisionDetectionRadius ) 
			)
			{
				carToMove->x -= signedMoveHspeedOtherCar;
				hspeedOtherCar = 0.0;
			}
			else
				keepGoingCarCollide = true;
		}

		if ( fabs(vspeedOtherCar) > 1.0 )
		{
			carToMove->y += signedMoveVspeedOtherCar;
			vspeedOtherCar -= signedMoveVspeedOtherCar;

			if ( 
			   i_TestCarCollisionWithOtherCars( carToMove->x, carToMove->y, carToMove->collisionDetectionRadius, carToMove->carId ) != NULL
			|| i_TestCarCollision( carToMove->x, carToMove->y, carToMove->halfWidth, carToMove->halfHeight, carToMove->collisionDetectionRadius ) 
			)
			{
				carToMove->y -= signedMoveVspeedOtherCar;
				vspeedOtherCar = 0.0;
			}
			else
				keepGoingCarCollide = true;
		}
	}
}


car i_CarCollision( car carEl )
{
	const double signedMoveHspeed = copysign( 1.0, carEl.hspeed );
	const double signedMoveVspeed = copysign( 1.0, carEl.vspeed );

	//start searching
	bool keepGoing = true;

	while( keepGoing )
	{
		keepGoing = false;

		//move car
		if ( fabs( carEl.hspeed ) > 1.0 )
		{
			carEl.x += signedMoveHspeed;
			carEl.hspeed -= signedMoveHspeed;

			//test if in wall
			car * collideCar = NULL;
			if ( 
				i_TestCarCollision( carEl.x, carEl.y, carEl.halfWidth, carEl.halfHeight, carEl.collisionDetectionRadius ) ||
				NULL != (collideCar = i_TestCarCollisionWithOtherCars( carEl.x, carEl.y, carEl.collisionDetectionRadius, carEl.carId )) 
			   )
			{
				carEl.hspeed = 0.0;
				carEl.x -= signedMoveHspeed; //undo last move
				carEl.speed *= CAR_WALL_SPEED_DECAY;

				//reduce speed
				if ( collideCar != NULL )
					i_MoveCollidedCar( collideCar, carEl.angle, copysign( MaxD( 2.0, fabs(carEl.speed) / CAR_COLLIDE_SPEED_TRANSFER ), carEl.speed ) );
						
			}
			else
				keepGoing = true;
		}
			
		if ( fabs( carEl.vspeed ) > 1.0 )
		{	
			carEl.y += signedMoveVspeed;
			carEl.vspeed -= signedMoveVspeed;
				
			//test if in wall
			car * collideCar = NULL;
			if ( 
				i_TestCarCollision( carEl.x, carEl.y, carEl.halfWidth, carEl.halfHeight, carEl.collisionDetectionRadius ) ||
				NULL != (collideCar = i_TestCarCollisionWithOtherCars( carEl.x, carEl.y, carEl.collisionDetectionRadius, carEl.carId )) 
			   )
			{
				carEl.vspeed = 0.0;
				carEl.y -= signedMoveVspeed; //undo last move
					
				//reduce speed
				carEl.speed *= CAR_WALL_SPEED_DECAY;

				if ( collideCar != NULL )
					i_MoveCollidedCar( collideCar, carEl.angle, copysign( MaxD( 2.0, fabs(carEl.speed) / CAR_COLLIDE_SPEED_TRANSFER ), carEl.speed ) );
			}
			else
				keepGoing = true;
		}
	}


	//apply angle movemnet
	carEl.angle -= carEl.deltaAngle;

	return carEl;
}


//new point based cd
car i_CarCollisionPoint( car carEl )
{
	return carEl;
}