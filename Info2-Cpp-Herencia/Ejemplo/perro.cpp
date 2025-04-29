#include "Perro.h"
#include <iostream>

Perro::Perro(const std::string& nombre) : Animal(nombre) {}

void Perro::ladrar() const {
    std::cout << nombre << " dice: ¡Guau guau!" << std::endl;
}
