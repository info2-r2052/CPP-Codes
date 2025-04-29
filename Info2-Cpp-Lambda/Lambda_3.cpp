#include <iostream>

int main() {
    int x = 5;

    // Función lambda que captura la variable 'x' por referencia y la multiplica por un valor dado
    int multiplicador = 2;
    auto lambda = [&x, multiplicador]() {
        x *= multiplicador;
    };

    std::cout << "Valor original de x: " << x << std::endl;

    // Llamamos a la función lambda
    lambda();

    std::cout << "Valor de x después de llamar a la función lambda: " << x << std::endl;

    return 0;
}
