// C++20 — I/O simulado "no bloqueante" a nivel del hilo que llama: otro hilo hace el sleep y
// devuelve el resultado por callback (patrón típico antes de futures/corrutinas).
// Compilar: g++ -std=c++20 -O2 -pthread -o ej02_callback ej02_no_bloqueante_callback.cpp
//
// Qué remarcar en clase:
// - read_async retorna de inmediato: el hilo del main puede seguir (no espera al disco aquí).
// - El trabajo lento corre en otro hilo; al terminar, invoca el callback (ojo: sincronización
//   si tocás estado compartido: acá solo imprimimos y el string se mueve al callback).
// - detach(): el hilo queda "suelto"; hay que asegurar que el proceso no termine antes del callback
//   (en este ejemplo el main duerme 3s a propósito). En apps reales suele haber un bucle de eventos
//   o joins explícitos.
// - No es magia: seguís usando un hilo del sistema para la espera; la diferencia es QUÉ hilo bloquea.

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

void read_async(std::function<void(std::string)> callback) {
    std::thread(
        [cb = std::move(callback)]() mutable {
            std::this_thread::sleep_for(2s);  // I/O en hilo de fondo
            cb("data from disk");
        })
        .detach();
}

void process(const std::string& data) {
    std::cout << "Processing: " << data << '\n';
}

int main() {
    std::cout << "Start\n";

    read_async([](std::string data) { process(std::move(data)); });

    std::cout << "Doing other work while waiting...\n";

    // Evita que main (y el proceso) terminen antes de que el hilo detached invoque el callback.
    std::this_thread::sleep_for(3s);

    std::cout << "Done\n";
    return 0;
}
