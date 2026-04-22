#include <iostream>
#include "Perro.h"

int main() {
    Perro miPerro("Firulais");

    miPerro.comer();     // Método heredado de Animal
    miPerro.ladrar();    // Método propio de Perro

    return 0;
}
