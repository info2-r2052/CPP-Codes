/*
 * LCD.cpp
 *
 *  Created on: 31 oct. 2023
 *      Author: gusta
 */

#include "Defines.h"

#define		PIN_LCD16X2_RS		0,1
#define		PIN_LCD16X2_E		0,14
#define		PIN_LCD16X2_D7		0,13
#define		PIN_LCD16X2_D6		0,11
#define		PIN_LCD16X2_D5		0,10
#define		PIN_LCD16X2_D4		0,9


Gpio LCD_E(PIN_LCD16X2_E, 1);
Gpio LCD_RS(PIN_LCD16X2_RS, 1);

Gpio LCD_D4(PIN_LCD16X2_D4, 1);
Gpio LCD_D5(PIN_LCD16X2_D5, 1);
Gpio LCD_D6(PIN_LCD16X2_D6, 1);
Gpio LCD_D7(PIN_LCD16X2_D7, 1);


//-----------------------
#define 	BORRAR_PANTALLA 	0x01
#define 	RESETEAR_CURSOR 	0x02
#define 	COMANDO 			0x00
#define 	DATO 				0x01
//
LCD.Escribir(COMANDO, BORRAR_PANTALLA);
LCD.Escribir(COMANDO, RESETEAR_CURSOR);

LCD.Escribir(DATO, 'H');
LCD.Escribir(DATO, 'O');
LCD.Escribir(DATO, 'L');
LCD.Escribir(DATO, 'A');

//Sensor: 100°
LCD.EscribirTexto("Sensor: ", 0, 0);
//                 0123456789
while(1){
	sprintf(Buffer, "%03d°", temp);
	LCD.EscribirTexto(Buffer, 0, 8);
}



//---------------------

void LCD::EscribirTexto(uint8_t *Texto, uint32_t Linea, uint32_t Columna)
{
	uint32_t offset = 0;

	offset = Linea * 40;
	offset += Columna;

	LCD.Escribir(COMANDO, 0x80 + offset);

	for(int i = 0 ; Texto[i] != 0 ; i++)
	{
		LCD.Escribir(DATO, Texto[i]);
	}
}

//void LCD::Escribir(uint8_t control, uint8_t dato)
//{
//	//E = 0;
//	LCD_E.Set(0);
//
////	Demora(1000);
//
//	//RS = 0;
//	LCD_RS.Set(control);
//
////	Demora(1000);
//
//	//E = 1;
//	LCD_E.Set(1);
//
////	Demora(1000);
//
//	// Escribo Datos
//	LCD_D0.Set(dato & 0x01);
//	LCD_D1.Set((dato >> 1) & 0x01);
//	LCD_D2.Set((dato >> 2) & 0x01);
//	LCD_D3.Set((dato >> 3) & 0x01);
//	LCD_D4.Set((dato >> 4) & 0x01);
//	LCD_D5.Set((dato >> 5) & 0x01);
//	LCD_D6.Set((dato >> 6) & 0x01);
//	LCD_D7.Set((dato >> 7) & 0x01);
//
////	Demora(1000);
//
//	//E = 0;
//	LCD_E.Set(0);
//}

void LCD::Escribir(uint8_t control, uint8_t dato)
{
	//E = 0;
	LCD_E.Set(0);

//	Demora(1000);

	//RS = 0;
	LCD_RS.Set(control);

//	Demora(1000);

	//E = 1;
	LCD_E.Set(1);

//	Demora(1000);

	// Escribo Datos
	LCD_D4.Set((dato >> 4) & 0x01);
	LCD_D5.Set((dato >> 5) & 0x01);
	LCD_D6.Set((dato >> 6) & 0x01);
	LCD_D7.Set((dato >> 7) & 0x01);

//	Demora(1000);

	//E = 0;
	LCD_E.Set(0);

	Demora(1000);

	//E = 1;
	LCD_E.Set(1);

//	Demora(1000);

	// Escribo Datos
	LCD_D4.Set(dato & 0x01);
	LCD_D5.Set((dato >> 1) & 0x01);
	LCD_D6.Set((dato >> 2) & 0x01);
	LCD_D7.Set((dato >> 3) & 0x01);

//	Demora(1000);

	//E = 0;
	LCD_E.Set(0);
}

//void Demora(uint32_t demora)
//{
//	Led.Set(1);
//
//	for(uint32_t i = 0 ; i < demora ; i++);
//
//	Led.Set(0);
//}

void LCD::Inicializar(void)
{
	//E = 0;
	LCD_E.Set(0);
}


