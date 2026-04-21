#include <iostream>
#include <thread>
#include <vector>

// Función que será ejecutada por el hilo
void funcion_hilo(int Texto) {
    std::cout << "Hola soy el hijo :" << Texto << std::endl;
}

int main() {
    // Crear un objeto thread y ejecutar la función con argumentos
    std::vector<std::thread> Hilo;

    for(int i = 0 ; i < 10 ; i++)
        Hilo.push_back(std::thread(funcion_hilo, i));

    // Esperar a que el hilo termine de ejecutar
    for (auto& thread : Hilo) {
        thread.join();
    }

    return 0;
}

