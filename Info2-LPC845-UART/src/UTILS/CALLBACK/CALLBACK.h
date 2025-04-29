/*
 * CALLBACK.h
 *
 *  Created on: 23 ago. 2023
 *      Author: gusta
 */

#ifndef UTILS_CALLBACK_CALLBACK_H_
#define UTILS_CALLBACK_CALLBACK_H_

// Definición de un tipo de puntero a función
typedef void (*FuncPtr)(void);

class CALLBACK {
private:
	void (*callback)(void);

public:
	CALLBACK();
	CALLBACK(void (*)(void));
	/*Este método debe ser implementado por las clases
	derivadas cada una resolverá que hacer con su Irq
	enganchada al  systick del sistema	*/
	virtual void Callback( void );

	void Set( void (*) (void) );
};

#endif /* UTILS_CALLBACK_CALLBACK_H_ */
