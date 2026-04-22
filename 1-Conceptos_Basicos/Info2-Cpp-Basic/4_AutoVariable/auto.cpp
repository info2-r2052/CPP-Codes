#include <iostream>

int main() {
    auto numero = 42;      // Se infiere como int
    auto pi = 3.1416;      // Se infiere como double
    auto letra = 'A';      // Se infiere como char

    std::cout << "Número: " << numero << ", Pi: " << pi << ", Letra: " << letra << std::endl;
    return 0;
}
