#include <future>
#include <iostream>
#include <thread>

// packaged_task empaqueta una funcion para ejecutarla despues y obtener un future
// con su valor de retorno. Es la pieza que muchos thread pools usan por dentro.

int suma(int a, int b) { return a + b; }

int main() {
    std::packaged_task<int()> tarea([]() { return suma(40, 2); });
    std::future<int> futuro = tarea.get_future();

    std::thread hilo(std::move(tarea));  // el task se mueve al hilo (solo ejecutable una vez)

    std::cout << "Resultado de la tarea empaquetada: " << futuro.get() << "\n";
    hilo.join();
    return 0;
}
