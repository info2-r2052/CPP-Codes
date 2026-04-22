#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define NULL 0

class String
{
private:
    char *p;

public:
    String()
    {
        p = NULL;
    }
    
    String(char *texto)
    {
        p = new char[strlen(texto) + 1];
        
        if(p == NULL)
        {
            return;
        }
        
        strcpy(p, texto);
    }
    
    String operator+(String X, String Y)
    {
        String temp;
        
        int Tamanio = strlen(X.p) + strlen(Y.p) + 1;  // Calculo el tamaño del string final
        
        temp.p = new char[Tamanio];                 // Solicito memoria
        
        if(temp.p == NULL)                          // Verifico
        {
            return;
        }
        
        strcpy(temp.textop, X.p);                          // Hola
        strcat(temp.p, Y.p);                        // HolaInfo
        
        return temp;
    }
    
    friend ostream& operator << (ostream &o,const String &p)
    {
        o << "El texto es: ";
        o << p.p;
    }
}

class StringNum : public String     //private
{
    StringNum(char *texto)
    {
        for(int i = 0 ; i < strlen(texto) ; i++)
        {
            if(texto[i] < '0' || texto[i] > '9')
            {
                // no hay numero
                return;
            }
        }
        // todo numero
        
        p = new char[strlen(texto) + 1];
        
        if(p == NULL)
        {
            return;
        }
        
        strcpy(p, texto);
    }
    
    StringNum operator+(StringNum X)
    {
        //Tarea
    }
}

int main(void)
{
    String A("Hola"), B("Info"), C;
    
    StringNum X("123"), Y("3"), Z("a");
    
    int Tamanio = A.strlen();   //Practica
    
    C = A + B;  //A.operator+(B)// HolaInfo
    
    Z = X + Y;  //X.operator+(Y)    // 126
    
    X.Imprimir();
    
    cout << X;
    
    int Indice = A.Buscar('o'); // Buscar letra en texto //Practica
    
    C.Imprimir();   //Practica
    
    cout << C;  //cout.operator<<(C)
}