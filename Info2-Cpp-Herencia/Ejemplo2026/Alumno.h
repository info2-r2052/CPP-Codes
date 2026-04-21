#include "Persona.h"

class Alumno : public Persona
{
    private:
        int legajo;

    public:
        int getLegajo();
        void SetLegajo(int legajo);
};