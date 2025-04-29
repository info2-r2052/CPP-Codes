#include <iostream>
#include "Persona.h"
#include "Docente.h"
#include "Alumno.h"

using std::cout;
using std::cin;
using std::endl;

Alumno Pedro(1, 1, "Pedro"), Juan(1, 1, "Juan");

Docente Gustavo;

int main(void)
{
    Juan.SetDni(-1);

    Juan.Imprimir();

    return -1;
}