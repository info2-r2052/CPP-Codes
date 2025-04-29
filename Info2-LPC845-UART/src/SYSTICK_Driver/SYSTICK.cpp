/*
 * SYSTICK.cpp
 *
 *  Created on: 15 ago. 2023
 *      Author: gusta
 */

#include "Defines.h"

extern Gpio ledG;
extern Gpio ledR;
extern Gpio ledB;

std::vector<CALLBACK*> vCallBack;

SYSTICK::SYSTICK( uint32_t FrecuenciaSystick )
{
	uint32_t  ticks ;

	ticks = FREQ_PRINCIPAL / FrecuenciaSystick;  		// ticks = Tsystic / Tclock ;

	if (ticks > MAX_TICKS)
		return;          		//* Reload value fuera de rango

	SysTick->RELOAD = ticks - 1;  	//* Cargamos la Cuenta

	SysTick->CURR = 0;   			//* SysTick Counter en 0 para que se recargue

	SysTick->CTRL = 7;	// ENABLE = 1, TICKINT = 1, CLKSOURCE = 1;

	return;
}

void SysTick_Handler(void)
{
	for (CALLBACK* q : vCallBack )
		q->Callback();
}
