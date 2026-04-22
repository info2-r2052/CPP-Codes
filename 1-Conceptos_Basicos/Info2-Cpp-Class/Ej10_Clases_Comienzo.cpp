// Clase Hora.
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// Definición del tipo de dato abstracto (ADT) Hora
class Hora 
{
    public:
       Hora();                        // constructor
       void estableceHora( int, int, int ); // establece hora, minuto, segundo
       void imprimeMilitar();          // imprime la hora en formato militar
       void imprimeEstandar();          // imprime la hora en formato estándar
    
    private:
       int hora;     // 0 - 23
       int minuto;   // 0 - 59
       int segundo;   // 0 - 59
}; // fin de la clase Hora

// El constructor Hora inicializa en cero a cada dato miembro.
// Garantiza que todos los objetos de Hora inician en un estado consistente.
Hora::Hora() 
{ 
    hora = minuto = segundo = 0; 
}

// Establece un nuevo valor de Hora por medio de la hora militar. Realiza verificaciones 
// de validación de los valores de los datos. Establece en cero a los valores inválidos.
void Hora::estableceHora( int h, int m, int s )
{
   hora = ( h >= 0 && h < 24 ) ? h : 0;
   minuto = ( m >= 0 && m < 60 ) ? m : 0;
   segundo = ( s >= 0 && s < 60 ) ? s : 0;
} // fin de la función estableceHora

// Imprime Hora en formato militar
void Hora::imprimeMilitar()
{
   cout << ( hora < 10 ? "0" : "" ) << hora << ":"
        << ( minuto < 10 ? "0" : "" ) << minuto;
} // fin de la función imprimeMilitar

// Imprime Hora en formato estándar
void Hora::imprimeEstandar()
{
   cout << ( ( hora == 0 || hora == 12 ) ? 12 : hora % 12 )
        << ":" << ( minuto < 10 ? "0" : "" ) << minuto
        << ":" << ( segundo < 10 ? "0" : "" ) << segundo
        << ( hora < 12 ? " AM" : " PM" );
} // fin de la función imprimeEstandar

// Controlador para probar la clase simple Hora
int main()
{
   Hora h;  // instancia el objeto t de la clase Hora

   system("PAUSE");
   cout << "La hora militar inicial es ";
   h.imprimeMilitar();
   cout << "\nLa hora estandar inicial es ";
   h.imprimeEstandar();

   h.estableceHora( 13, 27, 6 );
   cout << "\n\nLa hora militar despues de estableceHora es ";
   h.imprimeMilitar();
   cout << "\nLa hora estandar despues de estableceHora es ";
   h.imprimeEstandar();

   h.estableceHora( 99, 99, 99 );  // intenta establecer valores inválidos
   cout << "\n\nDespues de intentar establecer valores invalidos:"
        << "\nHora militar: ";
   h.imprimeMilitar();
   cout << "\nHora estandar: ";
   h.imprimeEstandar();
   cout << endl;

   system("PAUSE");
   return 0;
} // fin de la función main
