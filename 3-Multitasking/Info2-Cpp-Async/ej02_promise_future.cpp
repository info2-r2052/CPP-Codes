#include <future>
#include <iostream>
#include <thread>

// promise/future: un hilo "promete" un valor y otro lo "espera".
// Es util cuando el productor del resultado no es una funcion devuelta por async,
// sino codigo arbitrario (por ejemplo, lectura de red o de un sensor).

int main() {
    std::promise<int> promesa;
    std::future<int> futuro = promesa.get_future();

    std::thread trabajador([&promesa]() {
        std::cout << "[hilo] Calculando...\n";
        int resultado = 20 + 22;
        promesa.set_value(resultado);  // cumple la promesa (una sola vez)
    });

    std::cout << "[main] Esperando el valor...\n";
    std::cout << "[main] Recibido: " << futuro.get() << "\n";

    trabajador.join();
    return 0;
}
