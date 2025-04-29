#include <iostream>
#include <cstring>  // Para strlen y strcpy

using namespace std;

class String {
public:
    // Constructor por defecto
    String() {
        X = new char[1];
        X[0] = '\0';
    }

    // Constructor con parámetro
    String(const char* Cadena) {
        X = new char[strlen(Cadena) + 1];  // +1 para el carácter nulo '\0'
        strcpy(X, Cadena);
    }

    // Constructor de copia
    String(const String& otro) {
        X = new char[strlen(otro.X) + 1];
        strcpy(X, otro.X);
    }

    // Operador de asignación
    String& operator=(const String& otro) {
        if (this != &otro) { // Evitar autoasignación
            delete[] X;
            X = new char[strlen(otro.X) + 1];
            strcpy(X, otro.X);
        }
        return *this;
    }

    // Destructor
    ~String() {
        delete[] X;
    }

    // Inicializa el string con una nueva cadena
    void Inicializar(const char* Cadena) {
        delete[] X;
        X = new char[strlen(Cadena) + 1];
        strcpy(X, Cadena);
    }

    // Devuelve el tamaño de la cadena
    int Tamanio() const {
        return (int)strlen(X);
    }

    // Imprime el string
    void Imprimir() const {
        cout << X;
    }

private:
    char* X;
};

class String_Numerico : public String {
public:
    // Constructor por defecto
    String_Numerico() : String() {}

    // Constructor con validación numérica
    String_Numerico(const char* Cadena) {
        if (EsNumero(Cadena)) {
            Inicializar(Cadena);
        } else {
            Inicializar("");  // Si no es numérico, dejamos el string vacío
            cout << "Cadena Error: No es un número válido\n";
        }
    }

    // Verifica si la cadena contiene solo números
    bool EsNumero(const char* Cadena) const {
        int Tamanio = strlen(Cadena);
        for (int i = 0; i < Tamanio; i++) {
            if (Cadena[i] < '0' || Cadena[i] > '9') {
                return false;
            }
        }
        return true;
    }
};

int main() {
    String A("Hola "), B("Gustavo"), C;
    String_Numerico N("123"), M("Hola");  // "Hola" no es un número, debe mostrar error

    cout << "\nImprimo el valor de N: ";
    N.Imprimir();

    cout << "\nImprimo el valor de M: ";
    M.Imprimir();

    cout << "\nPresiona ENTER para salir...";
    cin.get();  // Espera entrada del usuario en lugar de system("PAUSE")
    return 0;
}
