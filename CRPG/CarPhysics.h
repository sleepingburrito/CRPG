#pragma once
#include <math.h>
#include <stdbool.h>

#include "CarsDataType.h"
#include "CarManager.h"
#include "MathEx.h"
#include "SDLtimingTools.h"
#include "Settings.h"
#include "MapDataTypes.h"
#include "MapMath.h"
#include "CarCollisionDetection.h"


void CarPhysicsStep( void )
{
	//==fixed time step==
	static timers fixTimeStep = 0;
	
	if ( !TimerPassed(fixTimeStep) )
		return;

	fixTimeStep = TimerSet( CAR_PHYSICS_TIMESTEP_MS );


	//==physics for all==
	for( size_t i = 0; i < CARS_COUNT_MAX; i++ )
	{
		//copy and active check
		if ( i_cars[i].active == false )
			continue;

		car carEl = i_cars[i];


		//==user io==
		//acceleration
		if ( carEl.throttle && !carEl.brakingReverse ) 
			carEl.speed += carEl.acceleration;

		//braking/reverse
		double brakeFriction = 0.0;
		if ( carEl.brakingReverse )
		{
			if ( carEl.speed > 0.0 ) //use brakes if moving forwards
				brakeFriction = carEl.breakingForceMax;
			else  //else if stopped reverse
				carEl.speed -= carEl.maxReverseAcceleration;
		}

		//handbrake
		if ( carEl.handBrake && carEl.drift <= carEl.driftHandbreakMax )
			carEl.drift += carEl.driftHandBreakIncrement;

		//speed reff
		const double absSpeed = fabs( carEl.speed );

		//turning left and right
		if ( fabs(carEl.turnAmount) <= carEl.turnLock && CAR_PHYSICS_NO_DRIFT == carEl.drift )
		{
			if ( STEERING_WHEEL_LEFT == carEl.steeringWheelState )
				carEl.turnAmount -= carEl.turnIncrement;

			if ( STEERING_WHEEL_RIGHT == carEl.steeringWheelState )
				carEl.turnAmount += carEl.turnIncrement;
		}


		//==turing==
		if ( CAR_PHYSICS_NO_DRIFT == carEl.drift ) //decay turning with speed
			carEl.turnAmount *= MaxD( carEl.turnDecay - ( absSpeed * carEl.turnSpeedDecayBySpeed ), 0.0 );

		//add a turn multiplyer at lower speeds
		double tmpAngle = KeepAngleInRangeD( carEl.angle );
		tmpAngle += carEl.turnAmount * MinD( carEl.turnSpeedLimit , pow( absSpeed, carEl.turnSpeedMultiplyer ) );
		carEl.deltaAngle = carEl.angle - tmpAngle;

		//drifting
		carEl.drift *= carEl.driftDecay;
		double driftComputed = 0;

		if ( carEl.drift <= CAR_PHYSICS_NO_DRIFT || carEl.speed == 0.0 )
			carEl.drift = CAR_PHYSICS_NO_DRIFT;
		else if ( fabs( carEl.turnAmount ) > CAR_PHYSICS_DRIFT_TURN_ACTIVATION_MIN ) //drift only when turing
			driftComputed = copysign( carEl.drift * carEl.diftAngleOffsetMax, carEl.turnAmount );
		

		//==speed==
		carEl.speed = copysign(
			MaxD( 
				0.0, 
				absSpeed
				- carEl.friction 
				- ( carEl.drag * absSpeed ) //air drag
				- brakeFriction //brakes
				- ( carEl.drift != CAR_PHYSICS_NO_DRIFT ? carEl.handbrakeBrakeAmount : 0 ) //handbrake
				)
			, carEl.speed );


		//==moving==
		//used for movment but not display
		const double angleWithDrift = tmpAngle - driftComputed;
		carEl.hspeed = carEl.speed * cos( angleWithDrift );
		carEl.vspeed = carEl.speed * sin( angleWithDrift );


		//==Collision Detection==
		carEl = i_CarCollision(carEl);


		//==copyback==
		i_cars[i] = carEl;
	}
}