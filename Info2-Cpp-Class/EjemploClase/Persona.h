#include <iostream>

#ifndef PERSONA
#define PERSONA
class Persona
{
    private:
        int dni;
        std::string nombre;
        int clave;

    public:

    Persona();

    Persona(const Persona &p);

    Persona(int _dni, std::string name);

    Persona(std::string name);

    ~Persona();

    void Imprimir(void);

    void Cargar(int _dni, std::string name);

    void SetDni(int DNI);

    int GetDni(void);

    std::string GetNombre(void);
    
    void SetNombre(std::string _nombre);
};

#endif
