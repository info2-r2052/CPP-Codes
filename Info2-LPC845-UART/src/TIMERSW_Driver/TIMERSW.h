/*
 * TIMERSW.h
 *
 *  Created on: 22 ago. 2023
 *      Author: gusta
 */

#ifndef TIMERSW_DRIVER_TIMERSW_H_
#define TIMERSW_DRIVER_TIMERSW_H_

#define 	NO_TECLA		0xFF

class TIMERSW : public CALLBACK{
public:
	uint32_t tiempo;
	uint8_t fin;
	uint32_t tiempoRecarga;
	void (*func)(void);

	TIMERSW();
	void Start(uint32_t tiempo, uint32_t tiempoRecarga, void (*func)(void));
	virtual void Descontar(void);

	void Callback( void );
};

#endif /* TIMERSW_DRIVER_TIMERSW_H_ */
