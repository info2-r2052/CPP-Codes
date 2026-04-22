#include <iostream>

int main() {
    int *arr = new int[5];  // Reservar memoria para 5 enteros
    
    for (int i = 0; i < 5; i++)
        arr[i] = i * 2;

    for (int i = 0; i < 5; i++)
        std::cout << arr[i] << " ";
    
    delete[] arr;  // Liberar memoria
    return 0;
}


