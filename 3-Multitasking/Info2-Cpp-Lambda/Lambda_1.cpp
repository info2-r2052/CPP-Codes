#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    
    // Ejemplo 1: Lambda simple
    auto lambda1 = []() {
        std::cout << "Hola, soy una lambda sin argumentos" << std::endl;
    };
    lambda1();

    // Ejemplo 2: Lambda con argumentos
    auto lambda2 = [](int x, int y) -> int {
        return x + y;
    };
    int resultado = lambda2(3, 4);
    std::cout << "El resultado de la suma es: " << resultado << std::endl;

    return 0;
}
