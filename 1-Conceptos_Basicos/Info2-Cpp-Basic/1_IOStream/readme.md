## Entrada y salida en C vs C++

En C, la entrada y salida estándar se maneja con `stdio.h`, utilizando funciones como `printf()` y `scanf()`.  
En C++, utilizamos `iostream`, que introduce `std::cout` para la salida y `std::cin` para la entrada, con operadores `<<` y `>>`, respectivamente.

---

### Ejemplo en C usando `stdio.h`
```c
#include <stdio.h>

int main() {
    int edad;
    printf("Ingrese su edad: ");
    scanf("%d", &edad);
    printf("Tienes %d años.\n", edad);
    return 0;
}
```

### Ejemplo en C++ usando `iostream`
```cpp
#include <iostream>

int main() {
    int edad;
    std::cout << "Ingrese su edad: ";
    std::cin >> edad;
    std::cout << "Tienes " << edad << " años.\n";
    return 0;
}
```

---

## Diferencias clave entre `stdio.h` y `iostream`

| Característica        | C (`stdio.h`)                      | C++ (`iostream`)                 |
|----------------------|--------------------------------|--------------------------------|
| **Entrada estándar** | `scanf("%d", &var);`           | `std::cin >> var;`             |
| **Salida estándar**  | `printf("Texto %d", var);`    | `std::cout << "Texto " << var;` |
| **Seguridad**       | Menos seguro (puede provocar desbordamientos) | Más seguro (manejo de tipos implícito) |
| **Formato**         | Se deben usar especificadores de formato (`%d`, `%s`, etc.) | Se adapta automáticamente al tipo de datos |
| **Encadenamiento**  | No soporta encadenamiento de operaciones | Permite encadenar con `<<` y `>>` |

---

## Ventajas de `iostream` en C++

1. **Más seguro:** No requiere especificadores de formato (`%d`, `%f`, `%s`), lo que reduce errores en la entrada/salida.  
2. **Encadenamiento de operadores:** Permite escribir código más limpio y legible.  
3. **Manejo automático de tipos:** `std::cin` y `std::cout` pueden trabajar con diferentes tipos sin necesidad de conversiones manuales.  
4. **Compatibilidad con objetos:** Funciona con clases y objetos mediante sobrecarga de operadores.  
5. **Soporte para manipuladores de flujo:** Permite modificar el formato de salida sin necesidad de funciones adicionales.  

Ejemplo de manipuladores:
```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.1415926535;
    std::cout << "Valor de pi con 4 decimales: " << std::fixed << std::setprecision(4) << pi << "\n";
    return 0;
}
```

---

## Desventajas y limitaciones de `iostream`

1. **Menor control sobre el formato:** Mientras que `printf()` permite definir con precisión el formato de salida, en `iostream` hay que usar manipuladores (`std::setw()`, `std::setprecision()`, etc.).  
2. **Rendimiento:** `iostream` puede ser más lento que `stdio.h` en algunos casos porque maneja tipos de datos de manera más abstracta.  
3. **Problemas con espacios en `std::cin`**:  
   - `std::cin >> variable;` ignora espacios en blanco, lo que puede ser problemático con `std::string`.  
   - Se recomienda usar `std::getline(std::cin, variable);` para leer líneas completas.  
   
   Ejemplo de problema con `std::cin`:
   ```cpp
   #include <iostream>
   #include <string>
   
   int main() {
       std::string nombre;
       std::cout << "Ingrese su nombre: ";
       std::cin >> nombre;
       std::cout << "Hola, " << nombre << "!\n";
       return 0;
   }
   ```
   **Problema:** Si el usuario ingresa `"Juan Pérez"`, solo se captura `"Juan"`.  
   
   Solución con `std::getline()`:
   ```cpp
   #include <iostream>
   #include <string>
   
   int main() {
       std::string nombre;
       std::cout << "Ingrese su nombre: ";
       std::getline(std::cin, nombre);
       std::cout << "Hola, " << nombre << "!\n";
       return 0;
   }
   ```
   Ahora se captura `"Juan Pérez"` correctamente.

---

## ¿Cómo compilar y ejecutar los programas?

### Compilación en C
Si estás en Linux/macOS, usa `gcc`:
```sh
gcc programa.c -o programa
./programa
```
En Windows con MinGW:
```sh
gcc programa.c -o programa.exe
programa.exe
```

### Compilación en C++
Si estás en Linux/macOS, usa `g++`:
```sh
g++ programa.cpp -o programa
./programa
```
En Windows con MinGW:
```sh
g++ programa.cpp -o programa.exe
programa.exe
```

### **¿Para qué sirve `using` en C++?**  

En C++, la palabra clave `using` tiene varias funciones, pero en este caso, se usa para **evitar escribir `std::` repetidamente** al usar elementos del espacio de nombres `std` (como `cout`, `cin` y `endl`).  

---

### **Ejemplo de `using std::cout;` en tu código**
```cpp
using std::cout;
using std::cin;
using std::endl;
```
Esto evita que tengas que escribir `std::cout`, `std::cin` y `std::endl` en cada línea, lo que hace que el código sea más limpio.  

#### **Alternativa sin `using`**
Si no usáramos `using`, tendríamos que escribir el prefijo `std::` cada vez:
```cpp
#include <iostream>

int main() {
    std::cout << "Hola, ingrese un número: ";
    int x;
    std::cin >> x;
    std::cout << "El número ingresado es: " << x << std::endl;
    return 0;
}
```

---
## **Otras formas de usar `using` en C++**  

### **1. `using namespace std;`**
En lugar de especificar cada elemento (`cout`, `cin`, etc.), podemos habilitar todo el espacio de nombres con:
```cpp
using namespace std;
```
**Ejemplo:**  
```cpp
#include <iostream>

using namespace std; // Ya no hace falta std::cout, std::cin, etc.

int main() {
    cout << "Hola, mundo!" << endl;
    return 0;
}
```
**Desventaja:** Puede generar **conflictos de nombres** si hay otros elementos con el mismo nombre en otro espacio de nombres.

---

### **2. `using` para crear alias de tipos**
También se puede usar `using` para **crear un alias de un tipo de dato complejo**, similar a `typedef`.

**Ejemplo con `using` en lugar de `typedef`**:
```cpp
#include <vector>

// Alias de tipo para un vector de enteros
using VectorEnteros = std::vector<int>;

int main() {
    VectorEnteros numeros = {1, 2, 3, 4, 5};

    for (int n : numeros) {
        std::cout << n << " ";
    }

    return 0;
}
```
**Equivalente con `typedef` (forma antigua en C++98)**
```cpp
typedef std::vector<int> VectorEnteros;
```
**Ventaja de `using`**: Es más claro y funciona mejor con plantillas.

---

### **3. `using` con punteros a funciones**
Si tienes una función con una firma larga, `using` puede ayudar a simplificarla.

**Ejemplo sin `using`**
```cpp
#include <iostream>

// Definimos un puntero a función que recibe dos enteros y devuelve un entero
int (*ptrFuncion)(int, int);

int suma(int a, int b) { return a + b; }

int main() {
    ptrFuncion = suma;
    std::cout << "Suma: " << ptrFuncion(4, 5) << std::endl;
    return 0;
}
```
**Con `using`, la sintaxis es más clara:**
```cpp
#include <iostream>

// Alias para un puntero a función
using FuncionSuma = int(*)(int, int);

int suma(int a, int b) { return a + b; }

int main() {
    FuncionSuma ptrFuncion = suma;
    std::cout << "Suma: " << ptrFuncion(4, 5) << std::endl;
    return 0;
}
```


