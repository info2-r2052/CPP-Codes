### Manejo de Memoria en C vs C++: `malloc/free` vs `new/delete`

El manejo de memoria es una de las diferencias clave entre C y C++. En C++, se introducen operadores que hacen que la administración de memoria sea **más segura** y **más fácil de manejar**.

---

## `malloc/free` (C) vs `new/delete` (C++)  

| Característica           | `malloc/free` (C)   | `new/delete` (C++) |
|-------------------------|--------------------|-------------------|
| **Devuelve**           | `void*` (requiere cast) | Tipo correcto |
| **Reserva memoria**    | `malloc(size_t)`   | `new` |
| **Libera memoria**     | `free(ptr)`        | `delete` |
| **Llama a constructor/destructor** | No | Sí (para objetos) |
| **Manejo en estructuras complejas** | Manual | Automático |

---

## Ejemplo en C (`malloc/free`)

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));  // Asignar memoria
    if (ptr == NULL) return 1;
    *ptr = 42;
    printf("Valor: %d\n", *ptr);
    free(ptr);  // Liberar memoria
    return 0;
}
```
**Ventajas de `malloc/free` en C:**  
- Compatible con cualquier versión de C.  
- Útil en programas donde se requiere interoperabilidad con otros lenguajes.

**Desventajas:**  
- `malloc` devuelve `void*`, por lo que necesita un **cast** explícito en C++.  
- `free` no llama al **destructor** de objetos en C++, lo que puede causar fugas de memoria.  
- No realiza verificación de tipos.

---

## Ejemplo en C++ (`new/delete`)

```cpp
#include <iostream>

int main() {
    int *ptr = new int;  // Asignar memoria
    *ptr = 42;
    std::cout << "Valor: " << *ptr << std::endl;
    delete ptr;  // Liberar memoria
    return 0;
}
```
**Ventajas de `new/delete` en C++:**  
- No necesita **cast** al asignar memoria.  
- `delete` llama al **destructor** de los objetos automáticamente.  
- Es más seguro y fácil de usar.  

**Desventajas:**  
- Puede haber **fugas de memoria** si olvidamos llamar a `delete`.  
- No es ideal en código moderno; se recomienda `std::unique_ptr` o `std::shared_ptr`.

---

## Uso con arreglos: `malloc/free` vs `new[]/delete[]`

### C (`malloc/free` con arrays)
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));  // Reservar memoria para 5 enteros
    if (!arr) return 1;
    
    for (int i = 0; i < 5; i++)
        arr[i] = i * 2;

    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    
    free(arr);  // Liberar memoria
    return 0;
}
```

### C++ (`new[]/delete[]` con arrays)
```cpp
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
```
? **Importante:**  
- Para liberar memoria de un **array dinámico**, usamos `delete[] arr;` en C++ (en lugar de `delete arr;`).
- En C++, es preferible usar **`std::vector` en lugar de `new[]/delete[]`**, ya que maneja la memoria automáticamente.

---

## C++ Moderno: `std::unique_ptr` y `std::shared_ptr`

En **C++ moderno (C++11 en adelante)**, se recomienda **evitar `new/delete`** y utilizar **smart pointers** para gestionar la memoria de manera segura.

### `std::unique_ptr` (propiedad exclusiva)
```cpp
#include <iostream>
#include <memory>  // Necesario para smart pointers

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);  // Manejo automático de memoria
    std::cout << "Valor: " << *ptr << std::endl;
    return 0;  // No es necesario llamar a delete
}
```
? Se libera automáticamente la memoria cuando `ptr` sale de su ámbito.

---

### `std::shared_ptr` (compartición de memoria)
```cpp
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1;  // Ahora hay dos referencias al mismo recurso

    std::cout << "Valor: " << *ptr1 << std::endl;
    return 0;  // La memoria se libera automáticamente cuando no hay más referencias
}
```
? Se usa cuando **varias partes del código** necesitan compartir un mismo recurso.  

---

## Resumen y Mejores Prácticas

| Método | Usa `malloc`/`free` | Usa `new`/`delete` | Usa `std::unique_ptr`/`std::shared_ptr` |
|--------|----------------|----------------|----------------|
| **Facilidad de uso** | Manual | Mejor que `malloc` | Automático |
| **Seguridad** | No llama a destructores | Puede haber fugas si olvidas `delete` | Se libera automáticamente |
| **Eficiencia** | Sin overhead | Rápido, pero manual | Ligero overhead en `shared_ptr` |



