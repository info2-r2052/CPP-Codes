#include <iostream>

class Coordenadas 
{
    private:
        int x, y;
    
    public:
        // Constructor con valores por defecto
        Coordenadas(int a = 0, int b = 0);
    
        // Sobrecarga del operador suma (binario)
        Coordenadas operator+(const Coordenadas& otra) const ;
    
        // Sobrecarga del operador resta (binario)
        Coordenadas operator-(const Coordenadas& otra) const ;
    
        // Sobrecarga del operador suma con constante
        Coordenadas operator+(int val) const ;
    
        // Sobrecarga del operador +=
        Coordenadas& operator+=(const Coordenadas& otra) ;
    
        // Sobrecarga del operador -=
        Coordenadas& operator-=(const Coordenadas& otra) ;
    
        // Sobrecarga del operador == (igualdad)
        bool operator==(const Coordenadas& otra) const ;
    
        // Sobrecarga del operador != (distinto)
        bool operator!=(const Coordenadas& otra) const ;
    
        // Sobrecarga del operador - (negativo unario)
        Coordenadas operator-() const ;
    
        // Pre-incremento (++A)
        Coordenadas& operator++();
    
        // Post-incremento (A++)
        Coordenadas operator++(int) ;
    
        // Sobrecarga del operador []
        int operator[](int index) const ;
    
        // Sobrecarga del operador << para impresión
        friend std::ostream& operator<<(std::ostream& os, const Coordenadas& c);
    
        // Método para calcular el módulo
        float Modulo() const;
    
        // Método para calcular distancia entre dos puntos
        float Distancia(const Coordenadas& otra) const;
    
        // Método para imprimir (opcional si usás <<)
        void Imprimir() const;
};