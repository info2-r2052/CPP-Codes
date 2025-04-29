# Ejemplo de Uso de std::set en C++

Este repositorio contiene un ejemplo de cómo utilizar `std::set` en C++ para almacenar datos unicos y en orden ascendente.

### **Uso de `std::set<int>` en C++**
`std::set<int>` es una estructura de datos en C++ que almacena elementos **únicos** en orden **ascendente** por defecto. Se basa en un árbol rojo-negro, lo que permite operaciones eficientes de búsqueda, inserción y eliminación en **O(log n)**.  


### ?? **Operaciones útiles en `std::set<int>`**
| Operación                  | Código                          | Complejidad |
|----------------------------|--------------------------------|-------------|
| Insertar un elemento       | `numeros.insert(42);`         | O(log n)    |
| Buscar un elemento         | `numeros.find(10);`           | O(log n)    |
| Eliminar un elemento       | `numeros.erase(5);`           | O(log n)    |
| Obtener el tamaño          | `numeros.size();`             | O(1)        |
| Verificar si está vacío    | `numeros.empty();`            | O(1)        |

---

## **Ventajas de `std::set<int>` sobre `std::vector<int>`**  
| Característica        | `std::set<int>` ?? | `std::vector<int>` ?? |
|----------------------|-----------------|----------------|
| **Valores únicos**  | ? Sí, no permite duplicados | ? No, permite duplicados |
| **Orden automático** | ? Sí, mantiene los elementos ordenados | ? No, el orden depende de la inserción |
| **Búsqueda rápida** | ? `O(log n)` (usa árboles balanceados) | ? `O(n)` (búsqueda lineal) |
| **Eliminación eficiente** | ? `O(log n)` | ? `O(n)`, requiere mover elementos |
| **Inserción ordenada** | ? `O(log n)` | ? `O(n)`, si se quiere mantener orden |

---

## **Ventajas de `std::vector<int>` sobre `std::set<int>`**  
| Característica         | `std::set<int>` ?? | `std::vector<int>` ?? |
|----------------------|----------------|----------------|
| **Acceso por índice (`arr[i]`)** | ? No se puede (requiere `std::next` o iterador) | ? Sí, acceso en `O(1)` |
| **Recorrido secuencial rápido** | ? Más lento (`O(log n)` por nodo) | ? Más rápido (`O(1)` en memoria contigua) |
| **Menor consumo de memoria** | ? Mayor (por los punteros de la estructura) | ? Menor (almacenado en un bloque contiguo) |
| **Inserción rápida al final** | ? `O(log n)` | ? `O(1)`, si hay espacio disponible |

---

## **¿Cuándo usar `std::set<int>`?**  
- Si **necesitas valores únicos** y que **estén ordenados automáticamente**.  
- Si **realizas muchas búsquedas**, ya que es más rápido (`O(log n)`).  
- Si **eliminas elementos con frecuencia**, ya que `std::set` lo hace en `O(log n)`, mientras que en `std::vector` es `O(n)`.  

## **¿Cuándo usar `std::vector<int>`?**  
- Si **necesitas acceder por índice (`arr[i]`)**.  
- Si **insertas datos en orden y los recorres secuencialmente** (es más eficiente).  
- Si el **tamaño es pequeño** y no necesitas búsquedas frecuentes.  

---

## **Ejemplo de comparación**
```cpp
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::vector<int> vec = {5, 10, 3, 10, 2};
    std::set<int> st = {5, 10, 3, 10, 2}; // Automáticamente ordena y elimina duplicados

    std::cout << "Vector: ";
    for (int x : vec) std::cout << x << " "; // ? 5 10 3 10 2
    std::cout << "\nSet: ";
    for (int x : st) std::cout << x << " "; // ? 2 3 5 10

    return 0;
}
```
**Salida esperada:**  
```
Vector: 5 10 3 10 2
Set: 2 3 5 10
```
En el `set`, **los valores están ordenados automáticamente y los duplicados han sido eliminados**.  

---


## Explicación del Dockerfile

El Dockerfile proporcionado se encarga de construir un contenedor Docker que ejecuta el código C++ dentro de un entorno controlado. Aquí hay una explicación de cada instrucción:

- `FROM debian:11.0-slim`: Utiliza la imagen base de Debian 11.0.
- `RUN apt-get update` y `RUN apt-get install -y libcpprest-dev g++`: Actualiza los paquetes disponibles e instala las dependencias necesarias para compilar el código C++.
- `COPY . .`: Copia todos los archivos del directorio actual al directorio de trabajo del contenedor.
- `RUN g++ SetExample.cpp -o SetExample.e`: Compila el archivo `SetExample.cpp` y genera un ejecutable llamado `SetExample.e` utilizando el compilador GCC.
- `CMD ["./SetExample.e"]`: Establece el comando predeterminado que se ejecutará cuando se inicie el contenedor. En este caso, ejecuta el ejecutable generado `SetExample.e`.

## Cómo usar el Dockerfile

Para ejecutar el programa utilizando Docker, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Coloca el archivo `SetExample.cpp` y el Dockerfile en un mismo directorio.
3. Abre una terminal y navega hasta el directorio que contiene los archivos.
4. Construye la imagen del contenedor ejecutando el siguiente comando:

   ```
    docker build -t setexample .
   ```

5. Una vez que se complete la construcción de la imagen, puedes ejecutar el programa en un contenedor Docker utilizando el siguiente comando:

   ```
    docker run -it --rm setexample
   ```