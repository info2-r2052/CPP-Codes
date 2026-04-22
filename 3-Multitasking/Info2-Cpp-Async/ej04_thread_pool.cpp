#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "thread_pool.hpp"

int trabajo(int id, int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return id * 10 + ms;
}

int main() {
    ThreadPool pool(3);

    std::vector<std::future<int>> resultados;
    for (int i = 0; i < 6; ++i) {
        int demora = 50 + i * 20;
        resultados.push_back(pool.enqueue(trabajo, i, demora));
    }

    std::cout << "Tareas enviadas al pool. El main puede seguir haciendo cosas.\n";
    for (std::size_t i = 0; i < resultados.size(); ++i) {
        std::cout << "Tarea " << i << " -> " << resultados[i].get() << "\n";
    }
    return 0;
}
