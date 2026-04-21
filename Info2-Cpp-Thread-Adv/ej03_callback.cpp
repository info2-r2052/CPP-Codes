// C++20 — Igual idea que ej02 (hilo + callback), pero en una clase pequeña: la tarea devuelve el
// string, otro callback procesa el éxito y, si la tarea lanza, un tercer callback recibe un mensaje.
// Compilar: g++ -std=c++20 -O2 -pthread -o ej03_callback ej03_callback.cpp
//
// Qué remarcar en clase:
// - Tres roles: trabajo pesado | qué hacer si salió bien | qué hacer si hubo excepción.
// - Sin plantillas: todo con std::string para leer el flujo de una vez.
// - detach(): el main no debe terminar antes del callback (acá duerme 3s a propósito).

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

class AsyncStringWork {
public:
    using Task = std::function<std::string()>;
    using OnSuccess = std::function<void(std::string)>;
    using OnError = std::function<void(const std::string&)>;

    AsyncStringWork(Task task, OnSuccess on_success, OnError on_error = OnError{}) {
        task_ = std::move(task);
        on_success_ = std::move(on_success);
        if (on_error) {
            on_error_ = std::move(on_error);
        } else {
            on_error_ = [](const std::string& message) {
                std::cerr << "[AsyncStringWork] " << message << '\n';
            };
        }
    }

    void start() {
        std::thread(
            [task = std::move(task_), on_success = std::move(on_success_), on_error = std::move(on_error_)]() mutable {
                try {
                    on_success(task());
                } catch (const std::exception& e) {
                    on_error(e.what());
                } catch (...) {
                    on_error("excepción desconocida");
                }
            })
            .detach();
    }

private:
    Task task_;
    OnSuccess on_success_;
    OnError on_error_;
};

void process(const std::string& data) {
    std::cout << "Processing: " << data << '\n';
}

int main() {
    std::cout << "Start\n";

    AsyncStringWork trabajo(
        []() -> std::string {
            std::this_thread::sleep_for(2s);
            return "data from disk";
            // throw std::runtime_error("fallo simulado");
        },
        [](std::string data) { process(std::move(data)); });

    trabajo.start();

    std::cout << "Doing other work while waiting...\n";

    std::this_thread::sleep_for(3s);

    std::cout << "Done\n";
    return 0;
}
