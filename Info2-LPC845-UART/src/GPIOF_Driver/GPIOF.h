/*
 * GPIOF.h
 *
 *  Created on: 5 set. 2023
 *      Author: gusta
 */

#ifndef GPIOF_DRIVER_GPIOF_H_
#define GPIOF_DRIVER_GPIOF_H_

#define 	CANTIDAD_ESTADOS_ESTABLES		4

class GPIOF : public Gpio , public CALLBACK
{
	private:
		uint8_t 	Contador;
		uint8_t 	Estado_Anterior;
		uint8_t 	Estado_Filtrado;

		void Antirebote(void);

	public:
		GPIOF(uint32_t _port, uint32_t _pin, uint32_t _direccion);
		uint32_t Read(void);
		void Callback( void );
};

#endif /* GPIOF_DRIVER_GPIOF_H_ */
