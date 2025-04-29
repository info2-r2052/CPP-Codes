#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

class Animal {
private:
    std::string nombre;

public:
    Animal(const std::string& nombre);
    void comer() const;
    std::string getNombre() const;
};

#endif
