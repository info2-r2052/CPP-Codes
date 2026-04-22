#include "coordenadas.h"
#include <iostream>

Coor::Coor(void)
{
    x = 0;
    y = 0;
}

Coor::Coor(const Coor &temp)
{
    x = temp.x;
    y = temp.y;
}

Coor::Coor(int Px , int Py)
{
    if(Px > 1000)
        Px = 1000;
    if(Py > 1000)
        Py = 1000;

    x = Px;
    y = Py;
}

Coor::Coor(float Px , int Py)
{
    x = (int)Px;
    y = Py;
}

Coor::~Coor()
{

}

Coor Coor::Suma(Coor x, Coor y)
{
    Coor temp;

    temp.x = a.x + b.x;
    temp.y = a.y + b.y;

    return temp;
}

Coor Coor::operator+(Coor b)
{
    Coor temp;

    temp.x = x + b.x;
    temp.y = y + b.y;

    return temp;
}

Coor Coor::operator+(int b)
{
    Coor temp;

    temp.x = x + b;
    temp.y = y + b;

    return temp;
}

char Coor::operator>(Coor b){
    if(x > b.x)
        return 1;
    else 
        return 0;
}

void Coor::Print(void)
{
    std::cout << "Las coordenadas son: " << x << "," << y << std::endl;
}

std::ostream& operator << (std::ostream &o,const Coor &p){
    o << "X=" << p.getX() << " Y=" << p.getY() << std::endl;
}