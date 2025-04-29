### 📌 **`auto` y `constexpr` en C++**  

C++ introduce dos características poderosas para mejorar la legibilidad y eficiencia del código:  

1. **`auto`** → Inferencia de tipos en tiempo de compilación.  
2. **`constexpr`** → Evaluación de expresiones en tiempo de compilación.  

---

## 🟢 **1. `auto` en C++**  

La palabra clave `auto` permite que el compilador deduzca el tipo de una variable automáticamente. Esto es especialmente útil cuando el tipo es complejo o tedioso de escribir.  

### 📌 **Ejemplo básico: Inferencia de tipos**  
```cpp
#include <iostream>

int main() {
    auto numero = 42;      // Se infiere como int
    auto pi = 3.1416;      // Se infiere como double
    auto letra = 'A';      // Se infiere como char

    std::cout << "Número: " << numero << ", Pi: " << pi << ", Letra: " << letra << std::endl;
    return 0;
}
```
✅ **Ventajas de `auto`:**  
- Reduce la repetición de tipos, evitando redundancia.  
- Útil para tipos complejos como iteradores y lambdas.  
- Hace el código más flexible y menos propenso a errores.  

---

### 📌 **Ejemplo con iteradores**  
En estructuras de datos como `std::vector`, el tipo de iterador puede ser largo y complicado. `auto` simplifica la sintaxis:  

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numeros = {1, 2, 3, 4, 5};

    // Uso de auto en iteradores
    for (auto it = numeros.begin(); it != numeros.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```
✅ **Beneficio**: `auto` evita tener que escribir `std::vector<int>::iterator`, lo que hace que el código sea más limpio.  

---

### 📌 **Ejemplo con funciones lambda**  
Las funciones lambda en C++ pueden tener tipos de retorno complicados. `auto` simplifica su uso:  
```cpp
#include <iostream>

int main() {
    auto suma = [](int a, int b) { return a + b; }; // Lambda con tipo inferido
    std::cout << "Suma: " << suma(10, 5) << std::endl;
    return 0;
}
```
✅ **Beneficio**: No es necesario especificar `std::function<int(int, int)>`, ya que `auto` lo deduce automáticamente.  

---

## 🔵 **2. `constexpr` en C++**  

La palabra clave `constexpr` permite definir constantes que son evaluadas en **tiempo de compilación**, lo que mejora el rendimiento al evitar cálculos en tiempo de ejecución.  

### 📌 **Ejemplo básico: Función evaluada en compilación**  
```cpp
#include <iostream>

constexpr int cuadrado(int x) { return x * x; }  // Evaluado en compilación

int main() {
    constexpr int resultado = cuadrado(5);  // Computado en compilación
    std::cout << "5^2 = " << resultado << std::endl;
    return 0;
}
```
✅ **Beneficio**: Como `cuadrado(5)` es evaluado en **tiempo de compilación**, el programa es más eficiente.  

---

### 📌 **Ejemplo con arrays de tamaño fijo**  
Antes de C++11, los tamaños de arrays debían ser constantes en tiempo de compilación (`const int`). `constexpr` mejora esto:  

```cpp
#include <iostream>

constexpr int getSize() { return 10; }

int main() {
    int arr[getSize()];  // Tamaño determinado en compilación
    std::cout << "Tamaño del array: " << sizeof(arr) / sizeof(arr[0]) << std::endl;
    return 0;
}
```
✅ **Beneficio**: `constexpr` permite que el compilador optimice mejor el uso de memoria.  

---

### 📌 **Ejemplo con `constexpr` y `std::array`**  
`constexpr` es útil con estructuras como `std::array`, que requieren tamaños en tiempo de compilación:  

```cpp
#include <iostream>
#include <array>

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    constexpr int tamano = 7;
    std::array<int, tamano> fibs = {fibonacci(0), fibonacci(1), fibonacci(2), fibonacci(3), fibonacci(4), fibonacci(5), fibonacci(6)};

    for (auto num : fibs) {
        std::cout << num << " ";
    }
    return 0;
}
```
✅ **Beneficio**: La serie de Fibonacci se calcula **antes de ejecutar el programa**, reduciendo costos computacionales.  

---

## 🎯 **Diferencias clave entre `auto` y `constexpr`**
| Característica | `auto` | `constexpr` |
|--------------|------------|------------|
| ¿Cuándo se evalúa? | En **tiempo de compilación** para deducir tipos, pero puede usarse en **tiempo de ejecución**. | Siempre en **tiempo de compilación**. |
| Propósito | Inferir tipos automáticamente. | Evaluar expresiones constantes en compilación. |
| Usos comunes | Variables, iteradores, lambdas. | Constantes, tamaños de arrays, cálculos precompilados. |

---
