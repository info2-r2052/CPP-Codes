#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

class Coordenadas
{
    private:
    int x,y;
    
    public:
    Coordenadas()
    {
        x = 0;
        y = 0;
    }
    
    Coordenadas(int A, int B)
    {
        x = A;
        y = B;
    }
    
    void Inicializar(int A, int B)
    {
        x = A;
        y = B;
    }
    
    void Imprimir()
    {
        cout << "X:" << x << " Y:" << y << endl;
    }
    
    Coordenadas Sumar(int Par_A, int Par_B)
    {
        Coordenadas Aux;
        
        Aux.x = x + Par_A;
        Aux.y = y + Par_B;
        
        return Aux;
    }

    Coordenadas Sumar(const Coordenadas &Obj)
    {
        Coordenadas Aux;
        
        Aux.x = x + Obj.x;
        Aux.y = y + Obj.y;
        
        return Aux;
    }
    
    Coordenadas Restar(int Par_A, int Par_B)
    {
        Coordenadas Aux;
        
        Aux.x = x - Par_A;
        Aux.y = y - Par_B;
        
        return Aux;
    }
    
    int Modulo(void)
    {
        float temp = (x*x) + (y*y);
        temp = sqrt(temp);
        
        return (int)temp;
    }
    
    int Distancia(Coordenadas A)
    {
        float temp = pow(x - A.x, 2) + pow(y - A.y, 2);
        temp = sqrt(temp);
        
        return (int)temp;
    }
};

struct TEMP
{
    int a;
    int b;
};

int main()
{
    TEMP    T1, T2;
    
    Coordenadas A(1,2), B, C, D;
    
    B.Inicializar(3,24);
    C.Inicializar(0,2);
    
    A.Imprimir();
    
    C = A.Sumar(1,2);
    
    C.Imprimir();
   
    C = B.Sumar(A);
    
    C.Imprimir();
    
    int Mod = C.Modulo();
    
    int Dist = A.Distancia(B);
    
}