// Las referencias se debe inicializar
#include <iostream>

using std::cout;
using std::endl;

int main()
{
   int x = 3, &y = x;  // y es un alias para x

   cout << "x = " << x << endl << "y = " << y << endl;
   y = 7;
   cout << "x = " << x << endl << "y = " << y << endl;

   system("PAUSE");
   return 0;
} // fin de la función main

