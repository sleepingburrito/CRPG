#pragma once
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "SDLStartWindow.h"

enum KeyStateIds
{
	KEY_STATE_DOWN,
	KEY_STATE_TAP,
	KEY_STATE_UP,
	KEY_STATE_COUNT_MAX
};

enum KeyIds
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_THROTTLE,
	KEY_BRAKE_REVERSE,
	KEY_HANDBRAKE,
	KEY_EXIT,
	KEY_COUNT_MAX
};

uint32_t ir_keys[ KEY_COUNT_MAX ];

void StartKeys( void )
{
	for( size_t i = 0; i < KEY_COUNT_MAX; i++ )
		ir_keys[i] = KEY_STATE_UP;
}

void i_UpdateKey( const uint32_t KeyId, const bool keyIsDown )
{
	if ( !keyIsDown )
		ir_keys[KeyId] = KEY_STATE_UP;
	else if ( ir_keys[KeyId] == KEY_STATE_TAP && keyIsDown )
		ir_keys[KeyId] = KEY_STATE_DOWN;
	else if ( ir_keys[KeyId] == KEY_STATE_UP && keyIsDown )
		ir_keys[KeyId] = KEY_STATE_TAP;

}

void UpdateKeysStep( void )
{
	for( size_t i = 0; i < KEY_COUNT_MAX; i++ )
		switch( i )
		{
			case KEY_LEFT:
				i_UpdateKey( KEY_LEFT, keyState[ SDL_SCANCODE_A ] );
			break;

			case KEY_RIGHT:
				i_UpdateKey( KEY_RIGHT, keyState[ SDL_SCANCODE_D ] );
			break;

			case KEY_THROTTLE:
				i_UpdateKey( KEY_THROTTLE, keyState[ SDL_SCANCODE_W ] );
			break;

			case KEY_BRAKE_REVERSE:
				i_UpdateKey( KEY_BRAKE_REVERSE, keyState[ SDL_SCANCODE_S ] );
			break;

			case KEY_HANDBRAKE:
				i_UpdateKey( KEY_HANDBRAKE, keyState[ SDL_SCANCODE_SPACE ] );
			break;

			case KEY_EXIT:
				i_UpdateKey( KEY_EXIT, keyState[ SDL_SCANCODE_ESCAPE ] );
			break;
		}
}