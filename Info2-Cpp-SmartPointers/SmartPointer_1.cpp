#include <iostream>
#include <memory>

struct Test {
    Test() { std::cout << "Construido\n"; }
    ~Test() { std::cout << "Destruido\n"; }
};

int main() {
    std::unique_ptr<Test> ptr1 = std::make_unique<Test>();
    std::unique_ptr<Test> ptr2 = std::move(ptr1); // Transferencia de propiedad
    return 0;
}