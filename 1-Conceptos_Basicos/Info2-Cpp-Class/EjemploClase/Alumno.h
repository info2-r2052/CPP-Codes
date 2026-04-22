
#include "Persona.h"

class Alumno : public Persona
{
    private:
        int legajo;

        std::string Materias[10];
        char Notas[10];

        int IndiceMateria = 0;

    public:

        void CargarMaterias(std::string Materia);

        Alumno(int _legajo, int _dni, std::string _nombre);
};