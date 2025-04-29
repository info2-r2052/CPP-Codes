# Pasaje de parámetros por referencia en C++  

Cuando llamamos a una función en C, los argumentos se pasan por **valor** de forma predeterminada. En C++, además del pasaje por valor, podemos pasar parámetros por **referencia**, lo que permite modificar el valor original sin necesidad de usar punteros.  

---

## Pasaje por valor vs Pasaje por referencia  

### Pasaje por valor (C y C++)  
En este caso, la función recibe una **copia** del argumento, lo que significa que cualquier modificación dentro de la función **no afecta el valor original**.  

**Ejemplo en C++ (pasaje por valor):**  
```cpp
#include <iostream>

void duplicar(int x) {  // Se pasa una copia del valor
    x *= 2;
}

int main() {
    int numero = 10;
    duplicar(numero);
    std::cout << "Numero despues de duplicar: " << numero << "\n"; // Sigue siendo 10
    return 0;
}
```
**Ventajas:**  
- Evita modificaciones accidentales del valor original.  
- Útil cuando no necesitamos modificar el parámetro.  

**Desventajas:**  
- Puede ser ineficiente para **estructuras grandes** como objetos o arrays porque se hace una copia completa.  

---

### Pasaje por referencia (C++)  
En este caso, la función recibe una **referencia al valor original**, lo que permite modificarlo directamente.  

**Ejemplo en C++ (pasaje por referencia):**  
```cpp
#include <iostream>

void duplicar(int &x) {  // Se pasa por referencia
    x *= 2;
}

int main() {
    int numero = 10;
    duplicar(numero);
    std::cout << "Numero despues de duplicar: " << numero << "\n"; // Ahora es 20
    return 0;
}
```
**Ventajas:**  
- **Evita copias innecesarias** y mejora el rendimiento, especialmente en estructuras grandes.  
- Permite modificar el valor original sin usar punteros.  

**Desventajas:**  
- Puede generar **efectos no deseados** si la modificación no es esperada.  
- No es obvio si la función modifica el argumento a menos que se consulte su implementación.  

---

### Pasaje por referencia constante (`const &`)  
Si queremos **evitar la copia**, pero sin modificar el argumento, usamos `const &`.  

```cpp
#include <iostream>

void imprimir(const std::string &mensaje) {  // No se copia, pero tampoco se puede modificar
    std::cout << mensaje << "\n";
}

int main() {
    std::string texto = "Hola, mundo!";
    imprimir(texto);  // Se pasa sin copiar
    return 0;
}
```
? **Ventajas:**  
- Ideal para **objetos grandes** (como `std::string`, `std::vector`) ya que evita copias innecesarias.  
- Garantiza que la función **no modificará** el argumento.  

? **Desventaja:**  
- No se puede modificar el parámetro dentro de la función.  

---

## ¿Cuándo usar cada tipo?  

| Modo                  | Modifica el valor original | Usa memoria extra | Eficiencia en estructuras grandes | Mejor práctica |
|----------------------|--------------------------|------------------|--------------------------------|----------------|
| **Por valor**        | No                     | Sí (copia)    | Ineficiente                  | Para tipos primitivos pequeños |
| **Por referencia**   | Sí                     | No (sin copia) | Eficiente                     | Cuando se requiere modificar el valor original |
| **Por referencia constante** | No | No (sin copia) | Eficiente | Para evitar copias en parámetros grandes |

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


