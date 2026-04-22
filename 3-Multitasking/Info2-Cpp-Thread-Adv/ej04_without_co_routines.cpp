#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <string>

// =======================
// Async con callbacks
// =======================

void read_async(std::function<void(std::string)> callback) {
    std::thread([callback]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        callback("data");
    }).detach();
}

void transform(std::string input, std::function<void(std::string)> callback) {
    std::thread([input, callback]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        callback("transformed " + input);
    }).detach();
}

void save(std::string data, std::function<void()> callback) {
    std::thread([data, callback]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        callback();
    }).detach();
}

// =======================
// Workflow (callback hell)
// =======================

int main() {
    std::cout << "Start\n";

    read_async([](std::string data) {
        transform(data, [](std::string result) {
            save(result, []() {
                std::cout << "done\n";
            });
        });
    });

    std::this_thread::sleep_for(std::chrono::seconds(5)); // mantener vivo
}