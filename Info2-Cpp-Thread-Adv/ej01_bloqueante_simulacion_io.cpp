// C++20 — I/O simulado BLOQUEANTE (sin corrutinas).
// Compilar: g++ -std=c++20 -O2 -pthread -o ej01_bloqueante ej01_bloqueante_simulacion_io.cpp
//
// Qué remarcar en clase:
// - El hilo actual queda ocupado en sleep: no avanza el flujo hasta que termina la "lectura".
// - Mientras bloquea, ese hilo no puede hacer otro trabajo útil en este modelo secuencial.
// - Si cada request bloqueara así, escalar a muchas operaciones concurrentes empuja a muchos hilos
//   (costoso en memoria y scheduling) frente a modelos donde el hilo hace otra cosa mientras espera.

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

[[nodiscard]] std::string read_from_disk() {
    std::this_thread::sleep_for(2s);  // simula I/O lento
    return "data from disk";
}

void process(const std::string& data) {
    std::cout << "Processing: " << data << '\n';
}

int main() {
    const auto start = std::chrono::steady_clock::now();

    const auto data = read_from_disk();  // bloquea hasta que "termina" el disco
    process(data);

    const auto end = std::chrono::steady_clock::now();
    std::cout << "Total time: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
              << "s\n";
    return 0;
}
