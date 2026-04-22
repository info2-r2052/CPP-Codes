#include <cstdlib>
#include <iostream>

using namespace std;

class String
{
    public:
        String()
        {
            X = new char[1];
            X[0] = 0;
        }
        
        String(char *Cadena)
        {
            X = new char[strlen(Cadena)];
            strcpy(X, Cadena);
        }
        
        ~String()
        {
            delete X;
        }
        
        String operator= (char * Cadena)
        {
            X = new char[strlen(Cadena)];
            strcpy(X, Cadena);
        }
        
        String operator= (String Cadena)
        {
            X = new char[strlen(Cadena.X)];
            strcpy(X, Cadena.X);
        }

        String operator== (String Cadena)
        {
            X = new char[strlen(Cadena.X)];
            strcpy(X, Cadena.X);
        }
        
        int Tamanio()
        {
            return (int)strlen(X);
        }
        
        String operator+(String Cadena)
        {
            String  Y;
            
            Y.X = new char[strlen(Cadena.X) + strlen(X)];
            
            strcpy(Y.X, X);
            strcat(Y.X, Cadena.X);
            
            return Y;
        }
        
        void Imprimir(void)
        {
            cout << X;
        }
        
    protected:
        char    *X;
};

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
                    X = "";
                    cout << "Cadena Error \n\r";
                    return;
                }
            }
            X = Cadena;  
        };
};

int main(int argc, char *argv[])
{
    String          A("Hola "), B("Gustavo"), C;
    String_Numerico N("123"), M("Hola");
    
    cout << "\n\rImprimo el valor de N=";
    N.Imprimir();
    cout << "\n\rImprimo el valor de M=";
    M.Imprimir();

    cout << "\n\r";
    system("PAUSE");
    return EXIT_SUCCESS;
}

