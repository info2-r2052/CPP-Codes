#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <string>

class Coor
{
    private:
    int x;
    int y;

    std::string pass = "1234";

    public:
    Coor(void);
    Coor(int Px , int Py);
    Coor(const Coor &temp);
    Coor(float Px , int Py);

    ~Coor();

    Coor Suma(Coor a, Coor b);
    Coor Suma(int var);
    Coor operator+(Coor b);
    char operator>(Coor b);

    void Print(void) const;
    friend ostream& operator << (ostream &o,const Coor &p);

    int getX() const;
    int getY() const;
    void setX(int valor);
    void setY(int valor);
};

#endif