/*
 * Teclado.cpp
 *
 *  Created on: 5 set. 2023
 *      Author: gusta
 */

#include "Defines.h"

extern std::vector<CALLBACK*> vCallBack;

Teclado::Teclado(){
	Buffer.clear();
	Contador = 0;
	Codigo_Tecla_Anterior = NO_TECLA;

	vCallBack.push_back(this);
}

uint8_t Teclado::Leer(void){
	if(!Buffer.empty())
	{
		uint8_t ultimoElemento = Buffer.back();
		Buffer.pop_back();
		return ultimoElemento;
	}
	return NO_TECLA;
}

void Teclado::Antirebote(void)
{
	uint8_t Codigo_Tecla_Actual;

	//Codigo_Tecla_Actual = ReadHW();

    if(Codigo_Tecla_Actual == NO_TECLA)
    {
        Contador = 0;
        Codigo_Tecla_Anterior = NO_TECLA;
        return;
    }

	if(Codigo_Tecla_Actual == Codigo_Tecla_Anterior)
	{
		Contador++;
		if(Contador >= CANTIDAD_ESTADOS_ESTABLES)
		{
			Buffer.push_back(Codigo_Tecla_Actual);
		}
	}
	else
	{
		Contador = 0;
	}

	Codigo_Tecla_Anterior = Codigo_Tecla_Actual;
}

void Teclado::Callback( void ){
	Antirebote();
}
