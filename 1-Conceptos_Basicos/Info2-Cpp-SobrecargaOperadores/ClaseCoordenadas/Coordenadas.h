#include<iostream>
#include<math.h>

class Coordenadas{
    private:
        int x;
        int y;    

    public:
        Coordenadas(){
            x = 0;
            y = 0;
        }

        Coordenadas(int px, int py){
            x = px;
            y = py;
        }

        void Imprimir(void)
        {
            std::cout << "X: " << x << " Y: " << y << std::endl;
        }

        float Distancia(Coordenadas &P1, Coordenadas &P2)
        {
            float temporal1 = pow((float)P1.x - (float)P2.x, 2);
            float temporal2 = pow((float)P1.y - (float)P2.y, 2);

            return sqrt(temporal1 + temporal2);
        }

        Coordenadas Suma(Coordenadas &P1, Coordenadas &P2){
            Coordenadas temp;

            temp.x = P1.x + P2.x;
            temp.y = P1.y + P2.y;

            return temp;
        }

        Coordenadas Suma(Coordenadas &Punto){
            Coordenadas temp;

            temp.x = Punto.x + x;
            temp.y = Punto.y + y;

            return temp;
        }

        Coordenadas operator+(Coordenadas &Punto){
            Coordenadas temp;

            temp.x = Punto.x + x;
            temp.y = Punto.y + y;

            return temp;
        }

        void Suma(Coordenadas &P1){
            x += P1.x;
            y += P1.y;
        }

        Coordenadas Resta(Coordenadas &P1, Coordenadas &P2){
            Coordenadas temp;

            temp.x = P1.x - P2.x;
            temp.y = P1.y - P2.y;

            return temp;
        }

};