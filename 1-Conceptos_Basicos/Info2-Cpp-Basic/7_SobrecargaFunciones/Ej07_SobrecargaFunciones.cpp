// Uso de funciones sobrecargadas
#include <iostream>

using std::cout;
using std::endl;

// Declaracion de la funcion "cuadrado" utilizando variables tipo int
int cuadrado( int x ) { return x * x; }

// Declaracion de la funcion "cuadrado" utilizando variables tipo double
double cuadrado( double y ) { return y * y; }

int main()
{
   cout << "El cuadrado del entero  7 es " << cuadrado( 7 )
        << "\nEl cuadrado del double 7.5 es " << cuadrado( 7.5 ) 
        << endl;    

   system("PAUSE");
   return 0;
} // fin de la función main
