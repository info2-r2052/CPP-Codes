#include <iostream>
#include <cmath>
#include "Coordenadas.h"

int main() {
    Coordenadas A(3, 5), B(2, 1), C;

    C = A + B;
    std::cout << "A + B = " << C << std::endl;

    C = A - B;
    std::cout << "A - B = " << C << std::endl;

    A += B;
    std::cout << "A += B -> A = " << A << std::endl;

    std::cout << "Comparación A == B: " << (A == B ? "Sí" : "No") << std::endl;

    std::cout << "Coordenada A: " << A << std::endl;
    std::cout << "Valor de A[0] = " << A[0] << ", A[1] = " << A[1] << std::endl;

    std::cout << "Módulo de A: " << A.Modulo() << std::endl;
    std::cout << "Distancia entre A y B: " << A.Distancia(B) << std::endl;

    std::cout << "Negativo de A: " << -A << std::endl;

    std::cout << "Pre-incremento de A: " << ++A << std::endl;
    std::cout << "Post-incremento de A: " << A++ << std::endl;
    std::cout << "Valor actual de A: " << A << std::endl;

    return 0;
}
