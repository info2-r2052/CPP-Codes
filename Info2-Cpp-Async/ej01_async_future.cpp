#include <chrono>
#include <future>
#include <iostream>
#include <thread>

// Simula algo pesado (red, disco, mucho CPU). Los mensajes muestran EN QUE HILO va el trabajo.
int cuadrado_con_pasos(int x, int cantidad_pasos, int ms_por_paso) {
    for (int paso = 1; paso <= cantidad_pasos; ++paso) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms_por_paso));
        std::cout << "  [TAREA] paso " << paso << "/" << cantidad_pasos << "\n" << std::flush;
    }
    return x * x;
}

void el_main_ocupa_su_tiempo(const char* titulo, int vueltas, int ms) {
    for (int i = 1; i <= vueltas; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout << titulo << " contador " << i << "/" << vueltas << "\n" << std::flush;
    }
}

int main() {
    std::cout << "========== 1) std::launch::async ==========\n";
    std::cout << "La idea: la funcion pesada puede ir en OTRO hilo.\n";
    std::cout << "Por eso vas a ver lineas [TAREA] y [MAIN] MEZCLADAS.\n\n";

    // Tarea larga: 5 pasos x 350 ms ~= 1,75 s (da tiempo a que el main imprima en paralelo).
    auto futuro_async =
        std::async(std::launch::async, cuadrado_con_pasos, 5, 5, 350);

    std::cout << "[MAIN] Ya pedi el trabajo; NO estoy bloqueado en el cuadrado todavia.\n";
    std::cout << "[MAIN] Hago otra cosa (como si fuera la interfaz, logs, otro calculo chico...)\n\n";

    el_main_ocupa_su_tiempo("[MAIN]   ", 8, 120);

    std::cout << "\n[MAIN] Listo con mis vueltas. Ahora pido el resultado con .get()...\n"
              << std::flush;
    const int resultado_async = futuro_async.get();
    std::cout << "[MAIN] Resultado del cuadrado de 5: " << resultado_async << "\n\n";

    std::cout << "========== 2) std::launch::deferred (contraste) ==========\n";
    std::cout << "Aca la tarea se POSPONE: hasta que llames .get() (o .wait()) no arranca.\n";
    std::cout << "Mientras tanto el main puede imprimir, pero la [TAREA] NO aparece todavia.\n\n";

    auto futuro_deferred =
        std::async(std::launch::deferred, cuadrado_con_pasos, 6, 4, 300);

    std::cout << "[MAIN] Recien pedi deferred: fijate que todavia NO hay [TAREA].\n\n";
    el_main_ocupa_su_tiempo("[MAIN]   ", 4, 100);

    std::cout << "\n[MAIN] Ahora llamo a .get() -> recien aca corre la tarea (suele ser el mismo hilo).\n"
              << std::flush;
    const int resultado_deferred = futuro_deferred.get();
    std::cout << "[MAIN] Cuadrado de 6: " << resultado_deferred << "\n\n";

    std::cout << "========== 3) Sin politica explicita (menos claro) ==========\n";
    std::cout << "std::async(sin launch::...) deja que el sistema elija async o deferred.\n";
    std::cout << "Para practicas: mejor usar siempre std::launch::async o ::deferred.\n";
    auto futuro_default = std::async(cuadrado_con_pasos, 7, 3, 200);
    const int resultado_default = futuro_default.get();
    std::cout << "[MAIN] Resultado: " << resultado_default << "\n";

    return 0;
}
