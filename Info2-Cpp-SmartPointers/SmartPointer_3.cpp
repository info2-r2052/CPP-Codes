#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

std::shared_ptr<int> sharedData = std::make_shared<int>(0);
std::mutex mtx;

void increment() {
    for (int i = 0; i < 5; i++) {
        std::lock_guard<std::mutex> lock(mtx);
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