#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ErrorMessages.h"

//returns the size in bytes
size_t LoadFileBin( const char * filename, void ** destination )
{
	size_t filesize = 0;

	//open the file
	FILE * file = NULL;
	errno_t err = fopen_s( &file, filename, "rb" );
	if ( err != 0 ||  NULL == file )
	{
		LogError( __FILE__, __func__, __LINE__ );
	}
	else
	{
		//find file size
		fseek( file, 0, SEEK_END );
		filesize = ftell(file);
		fseek( file, 0, SEEK_SET );

		//make file buffer
		if ( ( *destination = (void *)calloc( filesize, 1 ) ) == NULL ) 
			LogError( __FILE__, __func__, __LINE__ );

		//load and close file
		fread( *destination, ONE, filesize, file );
		fclose(file);
	}

	//return size
	return filesize;
}

int32_t SaveFileBin( const char * filename, size_t fileSizeBytes, const void * source )
{
	FILE *file = NULL;
	errno_t err = fopen_s( &file, filename, "wb" );

	if ( err != 0 || NULL == file ) 
		LogError( __FILE__, __func__, __LINE__ );
	else
	{
		fwrite( source, fileSizeBytes, 1, file );
		fclose(file);
	}

	return EXIT_SUCCESS;
}