
#include "coordenadas.h"
#include <iostream>


int main (void)
{
    Coor A(1,1);
    Coor B(2,2);
    Coor C;
    Coor D(A);

    A.Print();

    C = A + B;

    std::cout << A;

    //std::cout << "Las coordenadas son: " << C.x << "," << C.y << std::endl;

}