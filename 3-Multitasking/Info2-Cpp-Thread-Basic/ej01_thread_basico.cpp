// Ejemplo muy básico de std::thread (C++11+)
//
// Ideas clave para los alumnos:
// - El programa ya corre en un hilo: el de main().
// - std::thread(fn, args...) crea un hilo nuevo que ejecuta fn(args...).
// - join() bloquea hasta que ese hilo termina; hay que llamarlo (o detach)
//   antes de que se destruya el objeto std::thread, si no el programa aborta.
// - Sin sincronización, varios hilos escribiendo a la vez pueden mezclar texto
//   en la consola; aquí es solo didáctico.

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void saludarDesdeHilo(int id) {
    // Pausa artificial: ayuda a ver en clase que main y el hilo avanzan en paralelo
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Hilo secundario, id=" << id
              << ", std::thread::id=" << std::this_thread::get_id() << '\n';
}

int main() {
    std::cout << "main: comienzo, id del hilo principal = "
              << std::this_thread::get_id() << '\n';

    // --- Caso 1: un solo hilo secundario ---
    // std::thread(callable, arg1, arg2, ...): el primer parámetro es lo que se ejecuta
    // en el hilo nuevo (función, functor, lambda). El resto son argumentos que se
    // le pasan a ese callable (como en una llamada normal, por valor/referencia
    // según escribas aquí; ojo con referencias a variables locales que mueren).
    std::thread hiloUnico(saludarDesdeHilo, 0);
    std::cout << "main: ya lancé un hilo; sigo haciendo cosas aquí...\n";
    
    hiloUnico.join(); // esperar a que termine saludarDesdeHilo
    std::cout << "main: el hilo único ya terminó.\n\n";

    // --- Caso 2: varios hilos (patrón típico: vector + join en un segundo bucle) ---
    constexpr int kNumHilos = 5;
    std::vector<std::thread> hilos;
    
    // reserve reserva memoria para evitar realocaciones al agregar elementos al vector
    hilos.reserve(kNumHilos);

    for (int i = 0; i < kNumHilos; ++i) {
        hilos.emplace_back(saludarDesdeHilo, i + 1);
    }

    // Esperar (bloquear) hasta que cada hilo secundario termine su trabajo.
    // Es importante hacer join() a todos los hilos antes de que termine main,
    // de lo contrario podría abortar el programa.
    for (auto& h : hilos) {
        h.join();
    }

    std::cout << "main: todos los hilos terminaron. Fin.\n";
    return 0;
}