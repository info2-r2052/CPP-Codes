#include <iostream>
#include <cmath>
#include "Coordenadas.h"


Coordenadas::Coordenadas(int a, int b){
    x = a;
    y = b;
}

// Sobrecarga del operador suma (binario)
Coordenadas Coordenadas::operator+(const Coordenadas& otra) const {
    return Coordenadas(x + otra.x, y + otra.y);
}

// Sobrecarga del operador resta (binario)
Coordenadas Coordenadas::operator-(const Coordenadas& otra) const {
    return Coordenadas(x - otra.x, y - otra.y);
}

// Sobrecarga del operador suma con constante
Coordenadas Coordenadas::operator+(int val) const {
    return Coordenadas(x + val, y + val);
}

// Sobrecarga del operador +=
Coordenadas& Coordenadas::operator+=(const Coordenadas& otra) {
    x += otra.x;
    y += otra.y;
    return *this;
}

// Sobrecarga del operador -=
Coordenadas& Coordenadas::operator-=(const Coordenadas& otra) {
    x -= otra.x;
    y -= otra.y;
    return *this;
}

// Sobrecarga del operador == (igualdad)
bool Coordenadas::operator==(const Coordenadas& otra) const {
    return x == otra.x && y == otra.y;
}

// Sobrecarga del operador != (distinto)
bool Coordenadas::operator!=(const Coordenadas& otra) const {
    return !(*this == otra);
}

// Sobrecarga del operador - (negativo unario)
Coordenadas Coordenadas::operator-() const {
    return Coordenadas(-x, -y);
}

// Pre-incremento (++A)
Coordenadas& Coordenadas::operator++() {
    ++x;
    ++y;
    return *this;
}

// Post-incremento (A++)
Coordenadas Coordenadas::operator++(int) {
    Coordenadas temp = *this;
    ++(*this);
    return temp;
}

// Sobrecarga del operador []
int Coordenadas::operator[](int index) const {
    if (index == 0) return x;
    if (index == 1) return y;
    throw std::out_of_range("Índice inválido (sólo 0 o 1)");
}

// Sobrecarga del operador << para impresión
std::ostream& operator<<(std::ostream& os, const Coordenadas& c) {
    os << "(" << c.x << ", " << c.y << ")";
    return os;
}

// Método para calcular el módulo
float Coordenadas::Modulo() const {
    return std::sqrt(x * x + y * y);
}

// Método para calcular distancia entre dos puntos
float Coordenadas::Distancia(const Coordenadas& otra) const {
    return std::sqrt(std::pow(x - otra.x, 2) + std::pow(y - otra.y, 2));
}

// Método para imprimir (opcional si usás <<)
void Coordenadas::Imprimir() const {
    std::cout << *this << std::endl;
}

