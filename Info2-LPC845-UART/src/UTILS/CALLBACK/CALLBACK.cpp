/*
 * CALLBACK.cpp
 *
 *  Created on: 23 ago. 2023
 *      Author: gusta
 */

#include "Defines.h"

extern std::vector<CALLBACK*> vCallBack;

void CALLBACK::Callback(void)
{
	if ( callback )
		callback();
}

CALLBACK::CALLBACK( )
{
	Set(nullptr);
}

CALLBACK::CALLBACK( void (*CallBack) (void) )
{
	Set(CallBack);
}

void CALLBACK::Set( void (*CallBack) (void) )
{
	callback = CallBack;

	if ( callback )
		vCallBack.push_back( this );
}
