#include "Animal.h"
#include <iostream>

Animal::Animal(const std::string& nombre) : nombre(nombre) {}

void Animal::comer() const {
    std::cout << nombre << " está comiendo." << std::endl;
}

std::string Animal::getNombre() const {
    return nombre;
}
