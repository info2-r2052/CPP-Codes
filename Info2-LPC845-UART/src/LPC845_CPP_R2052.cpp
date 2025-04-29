/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "Defines.h"

void Led(void);
void Print(void);

SYSTICK Systick(1000);

Gpio ledG(1, 0, 1);
Gpio ledB(1, 1, 1);
Gpio ledR(1, 2, 1);

GPIOF	Pulsador(0, 4, 0);

TIMERSW Timer1;
//
//TIMERSW Timer2;

int main(void) {

	Timer1.Start(1000, 1000, Led);
//
//	Timer2.Start(2000, 2000, Print);

	UART0_Init(115200);

	ledG.Set(1);
	ledB.Set(1);
	ledR.Set(1);

    while(1) {

//    	Tecla = TECLADO_LEER();
//    	switch(Tecla)
//    	{
//    	case 1:
//    		MOVER_ROBOT_IZQUIERDA();
//    		break;
//    	case 2:S
//    		MOVER_ROBOT_returnDERECHA();
//    		break;
//    	case 3:
//    		ENCENDER_MAQUINA();
//    		break;
//    	}


    }
    return 0 ;
}

void Led(void){
	static uint8_t status = 0;

	UART0_Send((uint8_t*)">1000C<", 0);
	UART0_Send((uint8_t*)" Info2 ", 0);
	UART0_Send((uint8_t*)" Gus ", 0);

	if(status){
		status = 0;
		ledB.Set(1);
	}else{
		status = 1;
		ledB.Set(0);
	}
}

/*void ArmarPaquete_String(uint16_t Temperatura)
{
	uint8_t Buf[50];

	sprintf(Buf, ">T%04d..<", Temperatura);

	UART0_Send(Buf, 0);
}

void ArmarPaquete_Binario(uint16_t Temperatura)
{
	uint8_t Buf[50];

	Buf[0] = '>';
	Buf[1] = 'T';
	Buf[2] = (uint8_t)((Temperatura >> 8) & 0xff);
	Buf[3] = (uint8_t)((Temperatura >> 0) & 0xff);
	Buf[4] = '.';
	Buf[5] = '.';
	Buf[6] = '<';

	UART0_Send(Buf, 7);
}*/

void Print(void){
	static uint8_t status = 0;

	if(status){
		status = 0;
		ledG.Set(1);
	}else{
		status = 1;
		ledG.Set(0);
	}
}

//void MdE(void)
//{
//	switch(Estado)
//	{
//	.....
//	}
//}
//
//void Estado1(void)
//{
//	if(PIN.Read() == 1).......
//
//	if(PinFiltrado.Read() == 1)....
//}


















