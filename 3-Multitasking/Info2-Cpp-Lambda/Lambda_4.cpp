#include <iostream>
#include <vector>
#include <algorithm>

int func(std::string nombre)
{
    if(nombre == "Pepe")
        return true;
    else
        return false;
}

int main() {

    int resultado = 0;

    std::vector<std::string> alumnos = {    "Carlitos",
                                            "Carlitos",
                                            "Pepe",
                                            "Carlitos"};

    auto indice = std::find_if( alumnos.begin(),
                                alumnos.end(),
                                [](std::string nombre)
                                {   if(nombre == "Pepe")
                                        return true;
                                    else
                                        return false;
                                });
}