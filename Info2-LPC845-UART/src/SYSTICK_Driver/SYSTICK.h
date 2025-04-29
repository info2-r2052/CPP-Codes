/*
 * SYSTICK.h
 *
 *  Created on: 15 ago. 2023
 *      Author: gusta
 */

#ifndef SYSTICK_DRIVER_SYSTICK_H_
#define SYSTICK_DRIVER_SYSTICK_H_

#define FREQ_PRINCIPAL	(12000000UL)
#define MAX_TICKS (16777216UL)

extern "C" {
void SysTick_Handler(void);
}

class SYSTICK{
	public:
		SYSTICK( uint32_t FrecuenciaSystick );
};

#endif /* SYSTICK_DRIVER_SYSTICK_H_ */
