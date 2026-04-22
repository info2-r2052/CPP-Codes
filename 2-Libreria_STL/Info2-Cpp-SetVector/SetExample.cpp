#include <iostream>
#include <set>

int main() {
    std::set<int> numeros;

    // Insertar elementos en el set
    numeros.insert(10);
    numeros.insert(5);
    numeros.insert(20);
    numeros.insert(10);  // No se duplicará

    // Recorrer e imprimir los valores
    std::cout << "Elementos en el set:\n";
    for (int num : numeros) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Verificar si un número está en el set
    int buscar = 10;
    if (numeros.find(buscar) != numeros.end()) {
        std::cout << buscar << " está en el set.\n";
    } else {
        std::cout << buscar << " no está en el set.\n";
    }

    return 0;
}
