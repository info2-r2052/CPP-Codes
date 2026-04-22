#include <iostream>

int main() {
    int *ptr = new int;  // Asignar memoria
    *ptr = 42;
    std::cout << "Valor: " << *ptr << std::endl;
    delete ptr;  // Liberar memoria
    return 0;
}
