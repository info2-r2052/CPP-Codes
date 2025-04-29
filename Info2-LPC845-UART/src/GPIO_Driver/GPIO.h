/*
 * GPIO.h
 *
 *  Created on: 4 jul. 2023
 *      Author: gusta
 */

#ifndef GPIO_DRIVER_GPIO_H_
#define GPIO_DRIVER_GPIO_H_

class Gpio {
private:
	uint8_t port, pin, direccion;

public:
	Gpio();
	Gpio(uint32_t port, uint32_t pin, uint32_t direccion);
	void Set(uint32_t status);
	void Dir(uint32_t direccion);
	uint32_t Read(void);
};

#endif /* GPIO_DRIVER_GPIO_H_ */
