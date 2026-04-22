#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <string>

// =======================
// Task básica (coroutine)
// =======================
template<typename T>
struct Task {
    struct promise_type {
        T value;

        Task get_return_object() {
            return Task{ std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }

        void return_value(T v) { value = v; }
        void unhandled_exception() { std::exit(1); }
    };

    std::coroutine_handle<promise_type> handle;

    Task(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Task() { if (handle) handle.destroy(); }

    T get() { return handle.promise().value; }
};

// =======================
// Awaitable simple
// =======================
template<typename T>
struct AsyncOp {
    T result;

    bool await_ready() { return false; }

    void await_suspend(std::coroutine_handle<> h) {
        std::thread([this, h]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            h.resume(); // reanuda la coroutine
        }).detach();
    }

    T await_resume() { return result; }
};

// =======================
// Funciones async
// =======================
AsyncOp<std::string> read_async() {
    return AsyncOp<std::string>{"data"};
}

AsyncOp<std::string> transform(std::string input) {
    return AsyncOp<std::string>{"transformed " + input};
}

AsyncOp<void> save(std::string data) {
    return AsyncOp<void>{};
}

// =======================
// Coroutine principal
// =======================
Task<void> workflow() {
    auto data = co_await read_async();
    auto result = co_await transform(data);
    co_await save(result);

    std::cout << "done\n";
}

// =======================
// main
// =======================
int main() {
    workflow();

    // evitar que el programa termine antes
    std::this_thread::sleep_for(std::chrono::seconds(5));
}