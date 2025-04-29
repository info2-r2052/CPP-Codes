#include <iostream>
#include <memory>  // Para std::unique_ptr
#include <cstring> // Para strcpy y strlen

int main() {
    // Crear un unique_ptr para manejar un array dinámico de caracteres
    std::unique_ptr<char[]> texto = std::make_unique<char[]>(20);  // Reserva espacio para 20 caracteres

    // Copiar una cadena en el array
    strcpy(texto.get(), "Hola, mundo!");

    // Imprimir la cadena almacenada
    std::cout << "Texto almacenado: " << texto.get() << std::endl;

    // Se libera automáticamente la memoria al salir del scope
    return 0;
}
