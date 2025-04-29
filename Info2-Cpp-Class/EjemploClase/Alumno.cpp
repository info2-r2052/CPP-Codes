#include "Alumno.h"

void Alumno::CargarMaterias(std::string Materia){
    Materias[IndiceMateria] = Materia;
    IndiceMateria++;
    if(IndiceMateria > 10)
        IndiceMateria = 0;
}

Alumno::Alumno(int _legajo, int _dni, std::string _nombre){
    legajo = _legajo;
    SetDni(_dni);
    SetNombre(_nombre);
}
