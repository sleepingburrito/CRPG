#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * StringConCatNumber( const char * const string, const size_t number )
{
	//find how much space new string takes
	size_t fullStringSize = strlen( string );
	size_t lc = 1;
	while ( fullStringSize++, ( lc *= 10 ) <= number ); //find how long number is in base 10

	//make new string that needs to be freed
	char * tmpStr = (char*)calloc( ++fullStringSize, 1 );

	if ( tmpStr == NULL ) 
		LogError( __FILE__, __func__, __LINE__ );
	else
		sprintf_s( tmpStr, fullStringSize, "%s%zi", string, number );
	
	return tmpStr;
}

char * stringConcat( const char * const str1, const char * const str2 )
{
	//get memery
	size_t fullStringSize = strlen(str1) + strlen(str2) + 1;
	char * tmpStr = calloc( fullStringSize, 1 );
	if ( tmpStr == NULL ) 
		LogError( __FILE__, __func__, __LINE__ );
	else
		sprintf_s( tmpStr, fullStringSize, "%s%s", str1, str2 );

	return tmpStr;
}