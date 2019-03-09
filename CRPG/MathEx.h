#pragma once
#include <stdint.h>

#define PI 3.1415926535897932384626433832795
#define TWO_PI ( PI * 2.0 )
#define HALF_PI ( PI / 2.0 )
#define QUARTER_PI ( PI / 4.0 )
#define HALF_CIRCLE_DEGREES 180

#define ZERO 0
#define ONE 1
#define SQUARED 2


float MinF( const float value1, const float value2 )
{
	return value1 < value2 ? value1 : value2;
}

float MaxF( const float value1, const float value2 )
{
	return value1 > value2 ? value1 : value2;
}

int32_t Min( const int32_t value1, const int32_t value2 )
{
	return value1 < value2 ? value1 : value2;
}

int32_t Max( const int32_t value1, const int32_t value2 )
{
	return value1 > value2 ? value1 : value2;
}

double MinD( const double value1, const double value2 )
{
	return value1 < value2 ? value1 : value2;
}

double MaxD( const double value1, const double value2 )
{
	return value1 > value2 ? value1 : value2;
}

size_t MinSize( const size_t value1, const size_t value2 )
{
	return value1 < value2 ? value1 : value2;
}

size_t MaxSize( const size_t value1, const size_t value2 )
{
	return value1 > value2 ? value1 : value2;
}

double ClampD( double value, double min, double max )
{
	return MaxD( min, MinD( max, value ) );
}

float DegreesToRadiansf( const float angleDegrees )
{
	return angleDegrees * (float)PI / (float)HALF_CIRCLE_DEGREES;
}

float RadiansToDegreesf( const float angleRadians )
{
	return angleRadians * (float)HALF_CIRCLE_DEGREES / (float)PI;
}

double RadiansToDegrees( const double angleRadians )
{
	return angleRadians * (double)HALF_CIRCLE_DEGREES / PI;
}

void Swapf( float * value1, float * value2 )
{
	float swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}

void Swap( int * value1, int * value2 )
{
	int swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}

void SwaD( double * value1, double * value2 )
{
	double swap = *value1;
	*value1 = *value2;
	*value2 = swap;
}

float KeepAngleInRangeF( float angle ) 
{
	while ( angle > (float)TWO_PI || angle < ZERO ) 
		angle += copysignf( (float)TWO_PI, (float)TWO_PI - angle );

	return angle;
}

double KeepAngleInRangeD( double angle ) 
{
	while ( angle > TWO_PI || angle < ZERO ) 
		angle += copysign( TWO_PI, TWO_PI - angle );

	return angle;
}

double DistanceD( const double x, const double y, const double x2, const double y2 )
{
	return sqrt( pow( x - x2, (double)SQUARED ) + pow( y - y2, (double)SQUARED ) );
}

double SinProjection( double angle, double start, double distance )
{
	return distance * sin( angle ) + start;
}

double CosProjection( double angle, double start, double distance )
{
	return distance * cos( angle ) + start;
}