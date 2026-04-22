#include <cstdlib>
#include <iostream>
#include "String.h"

using namespace std;

class String_Numerico: public String
{
    public:
        String_Numerico(char *Cadena)
        {
            int Tamanio = strlen(Cadena);
            
            for(int i = 0 ; i < Tamanio ; i++)
            {
                if(Cadena[i] < '0' || Cadena[i] > '9')
                {
                    X = 0;
                    return;
                }
            }
            X = new char[strlen(Cadena)];
            strcpy(X, Cadena);
        };

        virtual void Imprimir(void)
        {
            if(X != 0)
                cout << "El numero es " << X;
            else
                cout << "No existe";
        }
};


int main(int argc, char *argv[])
{
    String          A("Hola "), B("Gustavo"), C;
    String_Numerico N("123"), M("Hola");
    
    cout << "\n\rN= ";
    N.Imprimir();
    cout << "\n\rM= ";
    M.Imprimir();

    cout << "\n\r";
    system("PAUSE");
    return EXIT_SUCCESS;
}

