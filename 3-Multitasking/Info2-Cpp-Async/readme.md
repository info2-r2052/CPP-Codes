# C++ asíncrono: `future`, `async` y un pool de hilos

## Idea general (comparación con C)

En C, si querés paralelismo, suele aparecer **pthreads** (`pthread_create`, `pthread_join`) o procesos. Tenés que pasar punteros, cuidar datos compartidos con mutex, etc.

En C++ el estándar ofrece abstracciones que **encapsulan** parte de eso:

| Concepto | Analogía sencilla |
|----------|-------------------|
| `std::thread` | Un `pthread` con interfaz de C++ |
| `std::mutex` | Como un mutex de pthreads |
| `std::future` / `std::promise` | Un **"cupón"** o **"ticket"**: alguien va a dejar un resultado y vos lo retirás cuando esté listo |
| `std::async` | Atajo para lanzar una función y recibir un `future` sin armar todo a mano |
| `std::packaged_task` | Empaqueta una función para ejecutarla después y ligarla a un `future` |

Nada de esto reemplaza entender **condiciones de carrera** y **mutex**: si dos hilos tocan la misma variable sin reglas, el programa es incorrecto igual que en C.

---

## Hilos mínimos antes de este repo (alineado con Info2-Cpp-Thread-Basic)

En paralelo al material de **async**, conviene haber visto un ejemplo mínimo de `std::thread` (por ejemplo `ej01_thread_basico.cpp` en el repo **Info2-Cpp-Thread-Basic**). Ese ejercicio resume:

- **Ya hay un hilo**: el de `main()`; `std::thread` agrega hilos secundarios.
- **Constructor** `std::thread(callable, arg1, …)`: el **primer** argumento es lo que se ejecuta en el hilo nuevo (función, functor o lambda); el **resto** son argumentos que se le pasan a ese *callable* (como en una llamada normal; cuidado con referencias a objetos que dejen de existir antes de que el hilo los use).
- **`join()`**: el hilo que llama espera a que termine el secundario; hay que hacer `join()` o `detach()` antes de destruir el `std::thread`, si no el programa termina en error.
- **Varios hilos**: patrón típico `std::vector<std::thread>` + `emplace_back(tarea, …)` en un bucle y **otro** bucle que hace `join()` sobre cada elemento.
- **Salida por consola**: varios hilos escribiendo sin sincronización pueden **mezclar** líneas; en el ejemplo básico es aceptable a fines didácticos; en código real suele usarse un mutex o un único hilo que agrega logs.

Los ejemplos de **este** repo (`async`, `promise`, `packaged_task`, pool) asumen que esa idea de “lanzar trabajo en otro hilo y esperar el fin” ya es familiar; acá el foco pasa a **cómo obtener un resultado** o **encolar trabajo** con `future` y compañía.

---

## Ejemplos en este repo

| Archivo | Estándar | Qué muestra |
|---------|----------|--------------|
| [`ej01_async_future.cpp`](ej01_async_future.cpp) | **C++17** | `std::async` + `std::future`: salida `[TAREA]` / `[MAIN]` mezclada con `std::launch::async`; contraste con `std::launch::deferred`. |
| [`ej02_promise_future.cpp`](ej02_promise_future.cpp) | **C++17** | Un hilo cumple una `std::promise` con `set_value`; el otro lee con `std::future::get()` y hace `join`. |
| [`ej03_packaged_task.cpp`](ej03_packaged_task.cpp) | **C++17** | `std::packaged_task` movido a un `std::thread`: patrón típico antes de encolar trabajo en un pool. |
| [`thread_pool.hpp`](thread_pool.hpp) + [`ej04_thread_pool.cpp`](ej04_thread_pool.cpp) | **C++17** | Cola de trabajos y varios hilos consumidores (`enqueue` → `std::future`). |
| [`ej05_coroutines_cpp20.cpp`](ej05_coroutines_cpp20.cpp) | **C++20** | `Task<T>` mínimo + `co_await` sobre un `std::future` (flujo parecido a async/await de C#). |

---

## Cómo compilar

**Requisitos:** compilador con soporte del estándar indicado. Con **g++** (MinGW / MSYS2 / Linux / macOS), los ejemplos con hilos y `std::async` suelen necesitar **`-pthread`**.

Desde la carpeta del repo (`Info2-Cpp-Async`):

```bash
# C++17 (ej01–ej04)
g++ -std=c++17 -O2 -pthread -o ej01_async_future      ej01_async_future.cpp
g++ -std=c++17 -O2 -pthread -o ej02_promise_future     ej02_promise_future.cpp
g++ -std=c++17 -O2 -pthread -o ej03_packaged_task      ej03_packaged_task.cpp
g++ -std=c++17 -O2 -pthread -o ej04_thread_pool        ej04_thread_pool.cpp

# C++20 + corrutinas (ej05)
g++ -std=c++20 -O2 -pthread -o ej05_coroutines_cpp20   ej05_coroutines_cpp20.cpp
```

**Ejecutar:** en Linux/macOS `./ej01_async_future`; en Windows `ej01_async_future.exe` (o el nombre que hayas puesto tras `-o`).

**MSVC:** usá `/std:c++17` o `/std:c++20` según el ejemplo; en versiones antiguas las corrutinas pueden requerir `/await` además de C++20 — consultá la documentación de tu versión.

Si **g++** falla con *No space left on device* en Windows, suele ser el disco o la carpeta temporal: liberar espacio o apuntar `TEMP` a un disco con lugar (cmd: `set TEMP=f:\mi_temp`, PowerShell: `$env:TEMP='f:\mi_temp'`).

---

## `std::async` y la política de lanzamiento

- `std::launch::async`: pide que el trabajo **pueda** ejecutarse en paralelo (otro hilo). No garantiza tiempos exactos, pero la idea es no bloquear al llamador en la llamada misma.
- `std::launch::deferred`: el trabajo **se pospone**; a menudo recién corre cuando hacés `get()` o `wait()` sobre el `future` (y puede correr en el mismo hilo que llama).
- Si no especificás política (`std::async(función, args...)`), el **sistema elige**: puede parecerse a `async` o a `deferred`. Para prácticas y código claro, **conviene ser explícitos** con `std::launch::async` o `deferred`.

`future.get()` **espera** el resultado (bloquea hasta que esté listo) y lo devuelve. Solo se debe llamar **una vez** por `future`.

---

## `promise` y `future`

- `std::promise<T>`: alguien va a producir un valor de tipo `T` (o una excepción).
- `promise.get_future()`: obtiene el `future` asociado.
- En otro hilo: `set_value`, `set_exception`, etc.

Sirve cuando el flujo no encaja en un solo `return` de una función pasada a `async` (por ejemplo, varias etapas o callbacks).

---

## `std::packaged_task`

Empaqueta un invocable y permite obtener un `future` de su resultado. Es útil para **encolar trabajos** que más adelante un hilo del pool ejecutará: el pool solo ve `function<void()>`, pero el llamador conserva el `future` con el tipo de retorno real.

---

## Pool de hilos (por qué no viene en el estándar)

El estándar no incluye un *thread pool* oficial. Patrón típico:

1. Varios hilos **trabajadores** esperan en una cola.
2. El productor **enciola** tareas (`std::function<void()>`).
3. Un trabajador despierta, saca una tarea y la ejecuta.

`thread_pool.hpp` es una versión **educativa y pequeña**: sirve para entender la idea; en proyectos grandes se suele usar **TBB**, **Boost.Asio**, **taskflow**, etc.

---

## C++20: corrutinas (`co_await`) y relación con .NET

En C# el patrón TAP (`async` / `await`) suspende el método y más adelante lo reanuda cuando el `Task` termina. En C++20 lo más cercano en el lenguaje son las **corrutinas**: `co_await`, `co_return`, y un tipo de retorno con `promise_type` (acá un `Task<T>` mínimo, parecido a `Task<T>` de .NET).

- `co_await await_future(std::move(future))` se parece a `await` cuando el resultado viene de un `std::future` (por ejemplo algo lanzado con `std::async`).
- `sync_wait(...)` en el ejemplo **solo** sirve para que `main` (que no es corrutina) bloquee hasta obtener el `int`: en una app real a menudo el hilo de UI o un bucle de eventos reanudarían la corrutina sin esta función auxiliar.

Compilación del ej05: ver bloque de comandos arriba (`-std=c++20`).

---

## Docker

```bash
docker build -t info2-async .
docker run --rm info2-async
```

La imagen compila los cinco ejemplos y los ejecuta en secuencia.

---

## Lecturas sugeridas

- Documentación de cppreference sobre [`std::async`](https://en.cppreference.com/w/cpp/thread/async), [`std::future`](https://en.cppreference.com/w/cpp/thread/future), [`std::packaged_task`](https://en.cppreference.com/w/cpp/thread/packaged_task), [corrutinas (C++20)](https://en.cppreference.com/w/cpp/language/coroutines).
