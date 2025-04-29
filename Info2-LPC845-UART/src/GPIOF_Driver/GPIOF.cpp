/*
 * GPIOF.cpp
 *
 *  Created on: 5 set. 2023
 *      Author: gusta
 */

#include "Defines.h"

extern std::vector<CALLBACK*> vCallBack;

GPIOF::GPIOF(uint32_t _port, uint32_t _pin, uint32_t _direccion) : Gpio(_port, _pin, _direccion)
{
	Estado_Anterior = 0;
	Contador = 0;
	Estado_Filtrado = 0;

	vCallBack.push_back(this);
}

void GPIOF::Callback(void)
{
	Antirebote();
}

uint32_t GPIOF::Read(void)
{
	return Estado_Filtrado;
}

void GPIOF::Antirebote(void)
{
	uint8_t Estado_Actual;

	Estado_Actual = Gpio::Read();

	if(Estado_Actual == Estado_Anterior)
	{
		Contador++;
		if(Contador >= CANTIDAD_ESTADOS_ESTABLES)
		{
			Estado_Filtrado = Estado_Actual;
		}
	}
	else
	{
		Contador = 0;
	}

	Estado_Anterior = Estado_Actual;
}
