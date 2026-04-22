// Uso de una plantilla de función
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template < class T , class Y>
T maximo( T valor1, Y valor2, T valor3 )
{
   T max = valor1;

   if ( valor2 > max )
      max = valor2;

   if ( valor3 > max )
      max = valor3;

   return max;
} // fin de la plantilla de función maximo

int main()
{
   int      int1, int3;
   char     int2;

   cout << "Introduzca tres valores enteros: ";
   cin >> int1 >> int2 >> int3;
   cout << "El valor entero maximo es : "
        << maximo( int1, int2, int3 );          // versión int

   double   doble1, doble3;
   char     doble2;

   cout << "\nIntroduzca tres valores double: ";
   cin >> doble1 >> doble2 >> doble3;
   cout << "El valor double maximo es: "
        << maximo( doble1, doble2, doble3 );   // versión double

   char char1, char3;
   int char2;

   cout << "\nIntroduzca tres caracteres: ";
   cin >> char1 >> char2 >> char3;
   cout << "El valor caracter maximo es: "
        << maximo( char1, char2, char3 )       // versión char
        << endl;

   system("PAUSE");
   return 0;
} // fin de la función main

