/*
 * GPIO.cpp
 *
 *  Created on: 4 jul. 2023
 *      Author: gusta
 */

#include "Defines.h"

Gpio::Gpio()
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);								// 7 = SWM
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 6) | (1 << 20) | (1 << 18);		// 6 = GPIO0	20 = GPIO1	18 = IOCON
}

Gpio::Gpio(uint32_t _port, uint32_t _pin, uint32_t _direccion)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);								// 7 = SWM
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 6) | (1 << 20) | (1 << 18);		// 6 = GPIO0	20 = GPIO1	18 = IOCON

	port = _port;
	pin = _pin;
	direccion = _direccion;

	Dir(direccion);
}

void Gpio::Set(uint32_t status)
{
	if(status)
		GPIO->SET[port] = (1 << pin);
	else
		GPIO->CLR[port] = (1 << pin);
}

//void Gpio::Set(void)
//{
//	GPIO->SET[port] = (1 << pin);
//}
//
//void Gpio::Clr(void)
//{
//	GPIO->CLR[port] = (1 << pin);
//}

void Gpio::Dir(uint32_t status)
{
	if(status)
		GPIO->DIRSET[port] = (1 << pin);
	else
		GPIO->DIRCLR[port] = (1 << pin);
}

uint32_t Gpio::Read(void)
{
	if(GPIO->PIN[port] & (1 << pin))
		return 1;
	else
		return 0;
}
