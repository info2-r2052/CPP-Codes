# Apunte sobre Punteros Modernos en C++

## Introducción
En C++ moderno, el uso de punteros crudos (`char*`, `int*`, etc.) ha sido reemplazado por punteros inteligentes (**smart pointers**), que gestionan la memoria de manera automática y evitan errores comunes como fugas de memoria y accesos indebidos.

Los principales punteros inteligentes en la STL de C++ son:
- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr` (para evitar ciclos de referencia en `std::shared_ptr`)

## Cuando usarlos:
-  **Usa `std::unique_ptr`** cuando solo debe haber un dueño del recurso.
-  **Usa `std::shared_ptr`** cuando necesitas compartir un recurso.
-  **Usa `std::mutex` o `std::atomic`** si `std::shared_ptr` se usa en hilos.

## `std::unique_ptr`
`std::unique_ptr` es un puntero exclusivo, lo que significa que **solo un `unique_ptr` puede poseer un objeto a la vez**. Cuando el `unique_ptr` sale de su alcance, el recurso se libera automáticamente.

### Ventajas:
-  Previene fugas de memoria, ya que la memoria se libera automáticamente.
-  No permite copias accidentales, evitando referencias no deseadas.
-  Más eficiente que `std::shared_ptr`, ya que no tiene contador de referencias.

## 📌 **Principales Métodos de `std::unique_ptr`**

| **Método** | **Ejemplo** | **Descripción** |
|------------|------------|---------------|
| `get()` | `ptr.get()` | Devuelve el puntero crudo. |
| `release()` | `ptr.release()` | Libera el puntero sin borrar el objeto. |
| `reset()` | `ptr.reset(new int(5))` | Asigna un nuevo objeto, liberando el anterior. |
| `swap()` | `ptr1.swap(ptr2)` | Intercambia punteros sin copiar. |
| `operator*` | `*ptr` | Obtiene el valor del objeto apuntado. |
| `operator->` | `ptr->metodo()` | Accede a los métodos del objeto apuntado. |


---

## 🟢 **1. `get()`: Obtener el puntero crudo**
📌 **Devuelve la dirección del objeto sin liberar la propiedad.**
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);

    std::cout << "Valor: " << *ptr << std::endl;
    std::cout << "Dirección del objeto: " << ptr.get() << std::endl;

    return 0;
}
```5}
✅ **Salida esperada:**  
```
Valor: 42  
Dirección del objeto: 0x561a1f8  
```

---

## 🟢 **2. `release()`: Libera la propiedad sin eliminar el objeto**
📌 **El `std::unique_ptr` deja de gestionar la memoria, pero no libera el objeto.**
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(100);
    
    int* raw_ptr = ptr.release(); // ptr ya no gestiona el objeto

    std::cout << "Valor liberado: " << *raw_ptr << std::endl;

    delete raw_ptr; // Hay que liberarlo manualmente

    return 0;
}
```
✅ **Cuidado:** Hay que liberar `raw_ptr` con `delete`, ya que `unique_ptr` deja de administrarlo.

---

## 🟢 **3. `reset()`: Liberar y reasignar**
📌 **Elimina el objeto actual y asigna otro.**
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(10);

    ptr.reset(new int(50)); // Libera el objeto anterior y asigna uno nuevo

    std::cout << "Nuevo valor: " << *ptr << std::endl;

    return 0;
}
```
✅ **Evita fugas de memoria sin necesidad de `delete`.**

---

## 🟢 **4. `swap()`: Intercambiar punteros**
📌 **Intercambia dos `unique_ptr` sin perder la propiedad de la memoria.**
```cpp
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> a = std::make_unique<int>(1);
    std::unique_ptr<int> b = std::make_unique<int>(2);

    a.swap(b); // Intercambia los valores

    std::cout << "a: " << *a << ", b: " << *b << std::endl;

    return 0;
}
```
✅ **Útil cuando se quiere cambiar dinámicamente de recurso.**

---

## 🟢 **5. `operator*` y `operator->`: Acceder al objeto**
📌 **Permiten acceder a los datos como si fuera un puntero normal.**
```cpp
#include <iostream>
#include <memory>

struct Persona {
    std::string nombre;
    void mostrar() { std::cout << "Nombre: " << nombre << std::endl; }
};

int main() {
    std::unique_ptr<Persona> ptr = std::make_unique<Persona>();
    ptr->nombre = "Carlos";
    ptr->mostrar(); // Usando ->

    return 0;
}
```
✅ **Funciona igual que un puntero tradicional con estructuras.**

---

## `std::shared_ptr`
`std::shared_ptr` permite compartir la propiedad del recurso entre múltiples instancias. Utiliza un **contador de referencias** para llevar un registro de cuántos `shared_ptr` están compartiendo el mismo recurso.

### Ventajas:
-  Múltiples objetos pueden compartir el mismo recurso.
-  Se libera automáticamente cuando ya no hay referencias.
-  Previene dobles liberaciones.

### Ejemplo de uso:
```cpp
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
```

## `std::shared_ptr` y concurrencia
`std::shared_ptr` **no maneja sincronización** para accesos concurrentes. Si se usa en hilos, es necesario proteger el acceso con `std::mutex` o `std::atomic`.

### Uso con `std::mutex`:
```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

std::shared_ptr<int> sharedData = std::make_shared<int>(0);
std::mutex mtx;

void increment() {
    for (int i = 0; i < 5; i++) {
        std::lock_guard<std::mutex> lock(mtx);
        (*sharedData)++;
        std::cout << "Thread " << std::this_thread::get_id() << " incrementa a " << *sharedData << std::endl;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Valor final: " << *sharedData << std::endl;
    return 0;
}
```

### Uso con `std::atomic`:
Si solo se modifican valores numéricos, `std::atomic` puede ser una mejor alternativa:
```cpp
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

std::shared_ptr<std::atomic<int>> sharedData = std::make_shared<std::atomic<int>>(0);

void increment() {
    for (int i = 0; i < 5; i++) {
        (*sharedData)++;
        std::cout << "Thread " << std::this_thread::get_id() << " incrementa a " << *sharedData << std::endl;
    }
}

int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    std::cout << "Valor final: " << *sharedData << std::endl;
    return 0;
}
```

## Comparación Final
| Característica            | `std::unique_ptr`       | `std::shared_ptr`       |
|--------------------------|-----------------------|-----------------------|
| Propiedad               | Exclusiva             | Compartida           |
| Copia permitida         | No                  | Sí                |
| Transferencia permitida | Sí (`std::move()`)  | Sí (incrementa contador) |
| Contador de referencias | No                  | Sí                |
| Rendimiento            | Más rápido (sin contador) | Más lento (mantiene contador) |
| Uso recomendado        | Recursos exclusivos   | Recursos compartidos |

## Cómo usar el Dockerfile

Para ejecutar el programa utilizando Docker, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Coloca el archivo `example.cpp` y el Dockerfile en un mismo directorio.
3. Abre una terminal y navega hasta el directorio que contiene los archivos.
4. Construye la imagen del contenedor ejecutando el siguiente comando:

   ```
    docker build -t example .
   ```

5. Una vez que se complete la construcción de la imagen, puedes ejecutar el programa en un contenedor Docker utilizando el siguiente comando:

   ```
    docker run -it --rm example
   ```

