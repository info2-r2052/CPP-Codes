// Comparación de una llamada por valor y una llama por referencia
// mediante referencias.
#include <iostream>

using std::cout;
using std::endl;

int cuadradoPorValor( int );
void cuadradoPorReferencia( int & );
                                                   
int main(void)
{
   int x = 2, z = 4;

   cout << "x = " << x << " antes de cuadradoPorValor\n"
        << "Valor devuelto por cuadradoPorValor: "
        << cuadradoPorValor( x ) << endl
        << "x = " << x << " despues de cuadradoPorValor\n" << endl;

   cout << "z = " << z << " despues de cuadradoPorReferencia" << endl;
   cuadradoPorReferencia( z );
   cout << "z = " << z << " despues de cuadradoPorReferencia" << endl;

   system("PAUSE");
   return 0;
} // fin de la función main

int cuadradoPorValor( int a )
{
   return a *= a;   // argumento de la llamada no modificada
} // fin de la función cuadradoPorValor

// Al enviar como parametro una referencia del dato podemos modificar directamente el valor enviado
void cuadradoPorReferencia( int &cRef )
{
   cRef *= cRef;    // argumento de la llamada modificada
} // fin de la función cuadradoPorReferencia
