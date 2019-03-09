#pragma once
#include <stdint.h>
#include <stdbool.h>


enum steeringWheelStates
{
	STEERING_WHEEL_LEFT,
	STEERING_WHEEL_RIGHT,
	STEERING_WHEEL_CENTER
};


typedef struct
{
	//base
	size_t carType; //id of the car type
	size_t carId; //uid per car instance
	bool active; //if not active physics will not run and car manager will give you out

	//movement state
	double x;
	double y;
	double hspeed;
	double vspeed;
	double angle;


	//physics states
	int32_t steeringWheelState;
	bool brakingReverse;
	bool handBrake;
	bool throttle;

	double speed;
	double deltaAngle; //cd will determin if you can do this and will update angle to what you can do
	double turnAmount;
	double drift; //starts at one and increases


	//other states
	double damage;


	//reference ( mostly read only )
	double width;
	double height;
	double halfWidth;
	double halfHeight;

	double acceleration;
	double maxReverseAcceleration;

	double drag;
	double friction;

	double handbrakeBrakeAmount;
	double breakingForceMax;

	double turnIncrement;
	double turnLock;
	double turnDecay;

	double turnSpeedMultiplyer; //make speed effect your turn speed
	double turnSpeedLimit; //after this speed, speed no longer contributes to turing
	double turnSpeedDecayBySpeed; //amount speed negatively affects turing ability

	double driftHandBreakIncrement;
	double driftHandbreakMax;
	double driftDecay;
	double diftAngleOffsetMax;

	double collisionDetectionRadius;
} car;