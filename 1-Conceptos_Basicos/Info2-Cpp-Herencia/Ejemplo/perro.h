#ifndef PERRO_H
#define PERRO_H

#include "Animal.h"

class Perro : public Animal {
public:
    Perro(const std::string& nombre);
    void ladrar() const;
};

#endif
