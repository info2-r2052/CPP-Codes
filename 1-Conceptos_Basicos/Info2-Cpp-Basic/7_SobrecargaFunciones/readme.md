### **Sobrecarga de Funciones en C++**  

La **sobrecarga de funciones** en C++ permite definir múltiples funciones con el mismo nombre pero con diferentes parámetros. El compilador selecciona la versión correcta de la función según los argumentos pasados en la llamada.  

#### **Reglas de Sobrecarga**  
1. **Diferente número de parámetros**  
2. **Diferentes tipos de parámetros**  
3. **Diferente orden de parámetros (si hay tipos distintos)**  

#### **Ejemplos de Sobrecarga**  

**Por número de parámetros**  
```cpp
#include <iostream>

// Función con un solo argumento
void mostrar(int a) {
    std::cout << "Número: " << a << std::endl;
}

// Función con dos argumentos
void mostrar(int a, int b) {
    std::cout << "Números: " << a << " y " << b << std::endl;
}

int main() {
    mostrar(10);
    mostrar(10, 20);
    return 0;
}
```

**Por tipo de parámetro**  
```cpp
void imprimir(int a) {
    std::cout << "Entero: " << a << std::endl;
}

void imprimir(double a) {
    std::cout << "Doble: " << a << std::endl;
}

void imprimir(const char* a) {
    std::cout << "Texto: " << a << std::endl;
}

int main() {
    imprimir(5);        // Llama a imprimir(int)
    imprimir(3.14);     // Llama a imprimir(double)
    imprimir("Hola");   // Llama a imprimir(const char*)
    return 0;
}
```

**Por orden de parámetros**  
```cpp
void calcular(int a, double b) {
    std::cout << "Entero y doble: " << a << ", " << b << std::endl;
}

void calcular(double a, int b) {
    std::cout << "Doble y entero: " << a << ", " << b << std::endl;
}

int main() {
    calcular(2, 3.5);  // Llama a calcular(int, double)
    calcular(3.5, 2);  // Llama a calcular(double, int)
    return 0;
}
```

#### **Consideraciones Importantes**  
- No se puede sobrecargar solo por el valor de retorno.  
- Puede causar ambigüedad si los parámetros son similares y hay conversiones implícitas.  
- Útil para mejorar la legibilidad y flexibilidad del código.  
