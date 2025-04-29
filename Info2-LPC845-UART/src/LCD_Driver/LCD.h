/*
 * LCD.h
 *
 *  Created on: 31 oct. 2023
 *      Author: gusta
 */

#ifndef LCD_DRIVER_LCD_H_
#define LCD_DRIVER_LCD_H_

class LCD {
	void Escribir(uint8_t control, uint8_t comando);
	void Inicializar(void);
};

#endif /* LCD_DRIVER_LCD_H_ */
