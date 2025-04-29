#include <iostream>

void imprimir(const std::string &mensaje) {  // No se copia, pero tampoco se puede modificar
    std::cout << mensaje << "\n";
}

int main() {
    std::string texto = "Hola, mundo!";
    imprimir(texto);  // Se pasa sin copiar
    return 0;
}

