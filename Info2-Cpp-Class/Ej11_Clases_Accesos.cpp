// Demostración de los operadores de acceso a los miembros de una clase . y ->
#include <iostream>

using std::cout;
using std::endl;

// Una clase sencilla Cuenta
class Cuenta 
{
    public:
        int x;
        
        // Fijense que esta clase no tiene constructor, ni destructor
        
        void imprime() 
        { 
            cout << x << endl; 
        }

        void imprime(int y) 
        { 
            cout << y << endl; 
        }
}; // fin de la clase Cuenta

int main()
{
   Cuenta contador,                // crea el objeto contador
         *ptrContador = &contador, // apuntador hacia contador
         &refContador = contador;  // referencia hacia contador

   cout << "Asigna 7 a x y lo imprime utilizando el nombre del objeto: ";
   contador.x = 7;       // asigna 7 al dato miembro x
   contador.imprime();     // llama a la función miembro imprime

   cout << "Asigna 8 a x y lo imprime utilizando una referencia: ";
   refContador.x = 8;    // asigna 8 al dato miembro x
   refContador.imprime();  // llama a la función miembro imprime

   cout << "Asigna 10 a x y lo imprime utilizando un apuntador: ";
   ptrContador->x = 10;  // asigna 10 al dato miembro x
   ptrContador->imprime(); // llama a la función miembro imprime

   cout << "Asigna 12 a x y lo imprime utilizando un apuntador: ";
   ptrContador->x = 12;  // asigna 12 al dato miembro x
   ptrContador->imprime(123); // llama a la función miembro imprime

   system("PAUSE");
   return 0;
} // fin de la función main

