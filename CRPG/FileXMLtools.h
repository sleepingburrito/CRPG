//starting and ending characters/attribute of the files/tags may not always be correct due to me hating strings
//XML must be formatted specially

#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#include "FileBin.h"
#include "ErrorMessages.h"
#include "Settings.h"
#include "MathEx.h"

typedef struct
{
	char tag[XML_TAG_STRING_COUNT_MAX];
	double value;
} XMLtags;

XMLtags * i_tagBuffer = NULL;
size_t i_tagCountXML = 0;

size_t i_searchIndex = 0;


void StartXML( void )
{
	if ( NULL == ( i_tagBuffer = (XMLtags *)calloc( XML_TAG_COUNT_MAX, sizeof(XMLtags) ) ) )
		LogError( __FILE__, __func__, __LINE__ );

	i_tagCountXML = 0;
}


void EndXML( void )
{
	free( i_tagBuffer );
	i_tagBuffer = NULL;
	i_tagCountXML = 0;
}


void ParseXMLAttributeValues( const char * const filename )
{
	//load the file
	char * const fileData = NULL;
	const size_t fileSize = LoadFileBin( filename, (void *)&fileData );

	//Parse tags
	for( size_t i = 0; i < fileSize && i_tagCountXML < XML_TAG_COUNT_MAX; i++ )
	{
		if ( fileData[i] == '=' ) //find a tag
		{
			//parse the tag
			for( size_t i2 = i; i2 != 0; i2-- )
			{
				if ( fileData[i2] == ' ' )  //find the start of the tag
				{
					if ( i_tagCountXML + 1 > XML_TAG_COUNT_MAX )
						LogError( __FILE__, __func__, __LINE__ );

					i2++; //move away from the space
					size_t indexMax = MinSize( i - i2, XML_TAG_STRING_COUNT_MAX - 1 );
					size_t indexMaxOffset = i2 + indexMax;

					size_t tmpIndex = 0;
					for( size_t i3 = i2; i3 < indexMaxOffset; i3++, tmpIndex++ )
					{
						i_tagBuffer[i_tagCountXML].tag[tmpIndex] = (char)tolower(fileData[i3]);
						i_tagBuffer[i_tagCountXML].tag[tmpIndex + 1] = 0;
					}
					break;
				}
			}

			//parse the number
			i += 2; //skip over the starting quotation mark and the equals sign
			char numberBuffer[XML_NUMBER_BUFFER_SIZE];
			numberBuffer[0] = 0;
			for( size_t i2 = 0; i2 < XML_NUMBER_BUFFER_SIZE - 1 && i < fileSize && fileData[i] != '"'; i++ )
			{
				if ( fileData[i] == '-' || isdigit( fileData[i] ) )
				{
					numberBuffer[i2] = fileData[i];
					numberBuffer[i2 + 1] = 0;
					i2++;
				}
			}
			i_tagBuffer[i_tagCountXML].value = atof( numberBuffer );

			i_tagCountXML++;
		}
	}

	//free the file
	free( fileData );
}


bool MoveNextXMLAttribute( const char * const Attribute )
{
	i_searchIndex++;

	while( i_searchIndex < i_tagCountXML )
	{
		if ( strcmp( Attribute, i_tagBuffer[i_searchIndex].tag ) == 0 )
			return true;
		
		i_searchIndex++;
	}

	if ( i_searchIndex >= i_tagCountXML )
		return false;
	
	return true;
}


bool CheckNextXMLAttribute( const char * const Attribute )
{
	if ( i_searchIndex + 1 >= i_tagCountXML )
		return false;

	if ( strcmp( Attribute, i_tagBuffer[i_searchIndex + 1].tag ) == 0 )
		return true;
	
	return false;
}


double GetXMLValueFromMove( void )
{
	return i_tagBuffer[i_searchIndex].value;
}