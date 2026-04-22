// Programa que suma dos enteros
#include <iostream>

int main(void)
{
    // Declaración de variables
   int entero1;

   // Nuevas formas de enviar al stout y recibir del stdin
   std::cout << "Introduzca el primer numero\n";  
   std::cin >> entero1;                      

   // Declaración de variables en cualquier parte del programa
   int entero2, resultado;                               

   std::cout << "Introduzca el segundo numero\n";
   std::cin >> entero2;                  
   resultado = entero1 + entero2;             
   
   // En el envio de cadenas al stdout se pueden enviar variables, esto es posible
   // gracias a la sobrecarga
   std::cout << "La suma es " << resultado << std::endl; 

   system("PAUSE");
   return 0;   // indica que el programa terminó de manera exitosa
} // fin de la función main
