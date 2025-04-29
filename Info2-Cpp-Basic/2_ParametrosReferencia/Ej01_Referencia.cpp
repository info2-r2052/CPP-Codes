#include <iostream>

void duplicar(int &x) {  // Se pasa por referencia
    x *= 2;
}

int main() {
    int numero = 10;
    duplicar(numero);
    std::cout << "Numero despues de duplicar: " << numero << "\n"; // Ahora es 20
    return 0;
}
