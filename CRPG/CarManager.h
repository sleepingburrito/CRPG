#pragma once
#include <stdbool.h>

#include "Settings.h"
#include "CarsDataType.h"

car * i_cars = NULL;

void StartCars( void )
{
	i_cars = (car*)calloc( CARS_COUNT_MAX, sizeof(car) );

	if ( NULL == i_cars )
	{
		LogError( __FILE__, __func__, __LINE__ );
		return; //make happy
	}

	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
		i_cars[i].active = false;
}

//returns null if no more cars
car * NextInactiveCar( void )
{
	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
		if ( !i_cars[i].active )
		{
			i_cars[i].active = true;
			return &i_cars[i];
		}

	return NULL;
}

size_t InactiveCarCount( void )
{
	size_t count = 0;

	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
		if ( !i_cars[i].active )
			count++;

	return count;
}