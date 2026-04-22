// Ejemplo C++20: corrutinas + co_await, analogo al flujo async/await de C# (TAP).
// Compilar: g++ -std=c++20 -O2 -pthread -o ej05_coroutines_cpp20 ej05_coroutines_cpp20.cpp

#include <chrono>
#include <concepts>
#include <coroutine>
#include <exception>
#include <future>
#include <iostream>
#include <optional>
#include <thread>
#include <utility>

// --- Task<T>: tipo de retorno minimo para una corrutina (como Task<T> en .NET) ---

template <typename T>
class Task {
public:
    struct promise_type {
        Task get_return_object() { return Task{std::coroutine_handle<promise_type>::from_promise(*this)}; }

        // suspend_never: el cuerpo corre al llamar la funcion hasta el primer co_await
        // (igual que en C# hasta el primer await); recien ahi se devuelve el Task al llamador.
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        template <typename U>
            requires std::convertible_to<U, T>
        void return_value(U&& value) {
            value_ = std::forward<U>(value);
        }

        void unhandled_exception() { exception_ = std::current_exception(); }

        std::optional<T> value_;
        std::exception_ptr exception_;
    };

    using Handle = std::coroutine_handle<promise_type>;

    explicit Task(Handle h) : handle_(h) {}
    Task(Task&& other) noexcept : handle_(std::exchange(other.handle_, {})) {}
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            destroy_if_needed();
            handle_ = std::exchange(other.handle_, {});
        }
        return *this;
    }
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    ~Task() { destroy_if_needed(); }

    Handle release_handle() { return std::exchange(handle_, {}); }

private:
    void destroy_if_needed() {
        if (handle_) {
            handle_.destroy();
            handle_ = {};
        }
    }

    Handle handle_{};
};

// Espera un std::future<T> dentro de una corrutina (parecido a await en C#).
template <typename T>
struct StdFutureAwaiter {
    std::future<T> fut;

    bool await_ready() const noexcept {
        return fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }

    // Bloquea hasta que el future este listo y reanuda esta corrutina en el mismo hilo.
    // (En produccion suele usarse un ejecutor / hilo de I-O que llama a resume sin bloquear.)
    void await_suspend(std::coroutine_handle<> h) {
        fut.wait();
        h.resume();
    }

    T await_resume() { return fut.get(); }
};

template <typename T>
StdFutureAwaiter<T> await_future(std::future<T>&& f) {
    return {std::move(f)};
}

// Ejecuta la corrutina hasta el final y devuelve el valor (bloqueante: para usar desde main).
template <typename T>
T sync_wait(Task<T>&& task) {
    typename Task<T>::Handle h = task.release_handle();
    if (!h) {
        throw std::runtime_error("sync_wait: Task vacio");
    }

    while (!h.done()) {
        h.resume();
    }

    auto& p = h.promise();
    if (p.exception_) {
        std::rethrow_exception(p.exception_);
    }
    T out = std::move(p.value_.value());
    h.destroy();
    return out;
}

// --- Simil de la documentacion de Microsoft: descarga + trabajo local + await ---

void DoIndependentWork() {
    for (int i = 1; i <= 4; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        std::cout << "  [DoIndependentWork] paso " << i << "/4\n" << std::flush;
    }
}

std::future<std::string> GetStringAsyncFake() {
    return std::async(std::launch::async, []() -> std::string {
        std::cout << "  [GetStringAsync] empezo en otro hilo...\n" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "  [GetStringAsync] termino\n" << std::flush;
        return std::string("<html>contenido</html>");
    });
}

Task<int> GetUrlContentLengthAsync() {
    std::cout << "[corrutina] Llamo a GetStringAsync (no bloquea el hilo del pool de async)\n";
    std::future<std::string> getStringTask = GetStringAsyncFake();

    std::cout << "[corrutina] Mientras tanto ejecuto DoIndependentWork (como en el diagrama)\n\n";
    DoIndependentWork();

    std::cout << "\n[corrutina] Llegue al co_await del string (equivale al await de C#)\n";
    std::string contents = co_await await_future(std::move(getStringTask));

    std::cout << "[corrutina] Ya tengo el string; calculo el largo\n";
    co_return static_cast<int>(contents.size());
}

int main() {
    std::cout << "=== C++20: corrutinas + co_await (flujo tipo TAP / async-await) ===\n\n";
    std::cout << "[main] sync_wait(...) espera el int; el argumento GetUrlContentLengthAsync()\n";
    std::cout << "[main] corre hasta el primer co_await (como un async de C# hasta el await).\n\n";

    const int len = sync_wait(GetUrlContentLengthAsync());

    std::cout << "\n[main] Longitud del contenido: " << len << "\n";
    return 0;
}
