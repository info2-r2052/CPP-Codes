
#include <iostream>
#include "Persona.h"

using std::cout;
using std::cin;
using std::endl;

Persona::Persona(){
    // Contructor
    nombre = "NN";
}

Persona::Persona(const Persona &p){
    dni = p.GetDni();
    nombre = p.nombre;
}

Persona::Persona(int _dni, std::string name){
    // Contructor
    dni = _dni;
    nombre = name;
}

Persona::Persona(std::string name){
    // Contructor
    nombre = name;
}

Persona::~Persona(){
    //Destructor
    cout << "Destructor " << nombre << endl;
}

void Persona::Imprimir(void){
    cout << " Dni: " << dni << " Nombre: " << nombre << endl;
}

void Persona::Cargar(int _dni, std::string name){
    dni = _dni;
    nombre = name;
}

void Persona::SetDni(int DNI){
    if(DNI < 0)
        return;

    dni = DNI;
}

int Persona::GetDni() const{
    return dni;
}

std::string Persona::GetNombre(void){
    return nombre;
}

void Persona::SetNombre(std::string _nombre){
    nombre = _nombre;
}



