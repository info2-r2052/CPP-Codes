#include "Alumno.h"

int Alumno::getLegajo(){
    return legajo;
}

void Alumno::SetLegajo(int _legajo)
{
    legajo = _legajo;

    SetDni(123);
}