#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

std::shared_ptr<std::atomic<int>> sharedData = std::make_shared<std::atomic<int>>(0);

void increment() {
    for (int i = 0; i < 5; i++) {
        (*sharedData)++;
        std::cout << "Thread " << std::this_thread::get_id() << " incrementa a " << *sharedData << std::endl;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Valor final: " << *sharedData << std::endl;
    return 0;
}