#pragma once
#include <stdint.h>
#include "SDLKeys.h"
#include "CarsDataType.h"
#include "CarManager.h"
#include "CarDatabase.h"

car * i_playersCar = NULL;

void SetPlayersCar( const size_t carTypeId, const double x, const double y )
{
	*i_playersCar = GetCarData( carTypeId );

	i_playersCar->x = x;
	i_playersCar->y = y;
}

void StartPlayersCar( void )
{
	if ( NULL == ( i_playersCar = NextInactiveCar() ) )
		LogError( __FILE__, __func__, __LINE__ );
}

void PlayersCarStep( void )
{
	//keys
	if ( ir_keys[KEY_LEFT] != KEY_STATE_UP && ir_keys[KEY_RIGHT] == KEY_STATE_UP )
		i_playersCar->steeringWheelState = STEERING_WHEEL_LEFT;
	else if ( ir_keys[KEY_RIGHT] != KEY_STATE_UP && ir_keys[KEY_LEFT] == KEY_STATE_UP )
		i_playersCar->steeringWheelState = STEERING_WHEEL_RIGHT;
	else
		i_playersCar->steeringWheelState = STEERING_WHEEL_CENTER;

	
	i_playersCar->brakingReverse = ir_keys[KEY_BRAKE_REVERSE] != KEY_STATE_UP;
	i_playersCar->handBrake      = ir_keys[KEY_HANDBRAKE]     != KEY_STATE_UP;
	i_playersCar->throttle       = ir_keys[KEY_THROTTLE]      != KEY_STATE_UP;
}