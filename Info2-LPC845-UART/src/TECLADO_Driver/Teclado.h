/*
 * Teclado.h
 *
 *  Created on: 5 set. 2023
 *      Author: gusta
 */

#ifndef TECLADO_DRIVER_TECLADO_H_
#define TECLADO_DRIVER_TECLADO_H_

class Teclado : public CALLBACK{
private:
	uint8_t Contador;
	uint8_t Codigo_Tecla_Anterior;
	std::vector<uint8_t> Buffer;

public:
	Teclado();
	uint8_t Leer(void);
	void Antirebote(void);
	void Callback( void );
};

#endif /* TECLADO_DRIVER_TECLADO_H_ */
