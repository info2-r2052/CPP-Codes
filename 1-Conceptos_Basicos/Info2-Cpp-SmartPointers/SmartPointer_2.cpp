#include <iostream>
#include <memory>

struct Test {
    Test() { std::cout << "Construido\n"; }
    ~Test() { std::cout << "Destruido\n"; }
};

int main() {
    std::shared_ptr<Test> ptr1 = std::make_shared<Test>();
    std::shared_ptr<Test> ptr2 = ptr1; // Ambos comparten la propiedad
    std::cout << "Contador de referencias: " << ptr1.use_count() << std::endl;
    return 0;
}