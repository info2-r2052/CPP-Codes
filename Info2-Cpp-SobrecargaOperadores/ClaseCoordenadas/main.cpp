#include "Coordenadas.h"

Coordenadas Pos1(1,1) , Pos2(2,2) , Pos3; 

int main(void)
{
    Pos3 = Pos1.Suma(Pos1, Pos2);

    Pos3 = Pos1.Suma(Pos2);

    Pos3 = Pos1 + Pos2;

    Pos3.Imprimir();
    
    return -1;
}