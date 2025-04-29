// Uso de una función inline para calcular
// el volumen de un cubo.
#include <iostream>

// Con estas sentencias nos ahorramos de tipear std:: cada vez que envias datos a pantalla
using std::cout;
using std::cin;
using std::endl;

// El comando inline sirve para crear "funciones" donde el codigo es repeti cada vez que se la llama
inline double cubo( const double s ) { return s * s * s; }

int main(void)
{
  double lado;

  for ( int k = 1; k < 4; k++ ) 
  {
   	  cout << "Introduzca la longitud de un lado del cubo:  ";
      cin >> lado;
      cout << "El Volumen del cubo con lado " 
           << lado << " es " << cubo( lado ) << endl;
  } // fin de for

   system("PAUSE");
   return 0;
} // fin de la función main

