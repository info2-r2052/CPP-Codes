#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    int resultado = 0;
    
    // Ejemplo 3: Lambda con captura
    int numero = 5;
    auto lambda3 = [numero](int x) -> int {
        return numero * x;
    };
    resultado = lambda3(3);
    std::cout << "El resultado de la multiplicación es: " << resultado << std::endl;

    // Ejemplo 4: Utilizando una lambda con std::find_if
    std::vector<int> numeros = {1, 2, 3, 4, 5};
    auto it = std::find_if(numeros.begin(), numeros.end(), [](int n) {
        return n % 2 == 0;
    });
    if (it != numeros.end()) {
        std::cout << "El primer número par es: " << *it << std::endl;
    }
    return 0;


    return 0;
}
