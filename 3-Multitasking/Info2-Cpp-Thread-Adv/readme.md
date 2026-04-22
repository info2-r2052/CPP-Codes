# Hilos y I/O: bloqueante vs no bloqueante (y corrutinas)

Este directorio complementa la charla sobre **qué hilo está esperando**. Los ejemplos usan **C++20** (`std::chrono_literals`, `[[nodiscard]]`, etc.). Los archivos `ej01`–`ej03` y `ej04_without_co_routines` se centran en **callbacks y hilos** sin `co_await`; `ej04_co_routines.cpp` muestra el mismo tipo de flujo con **corrutinas**.

La “lectura de disco” se simula con `std::this_thread::sleep_for`: es solo didáctica; en un programa real el bloqueo vendría del sistema operativo o de una API de I/O.

---

## Qué son los hilos (en palabras sencillas)

Un **hilo** es una secuencia de instrucciones que el procesador va ejecutando. Tu programa puede tener **varios hilos**: cada uno avanza por su cuenta, pero comparten la misma memoria del proceso (con cuidado: si dos hilos escriben lo mismo a la vez, hay que sincronizar).

Imaginá una **caja registradora con una sola persona**: si esa persona tiene que ir al depósito a buscar mercadería (operación lenta), la fila de clientes **se queda parada**. Eso es parecido a **I/O bloqueante en el mismo hilo**: mientras “espera al disco”, no hace otra cosa útil en ese flujo.

Si abrís **otro mostrador** (otro hilo), la persona del mostrador principal puede seguir atendiendo mientras **otra persona** va al depósito. El trabajo lento sigue existiendo; lo que cambia es **quién** está esperando. En estos ejemplos, `std::thread` crea ese “otro mostrador”: un hilo nuevo que hace el `sleep` (I/O simulado) y, cuando termina, avisa al resto del programa (por ejemplo con un **callback**).

**Resumen:** los hilos no hacen que el disco sea más rápido; permiten que **un hilo espere** mientras **otro sigue ejecutando** otra lógica.

---

## Ejemplos

| Archivo | Qué muestra |
|---------|-------------|
| [`ej01_bloqueante_simulacion_io.cpp`](ej01_bloqueante_simulacion_io.cpp) | `read_from_disk()` hace el `sleep` en el **mismo** hilo que llama: el flujo no sigue hasta que termina la operación lenta. Se mide el tiempo total con `steady_clock`. |
| [`ej02_no_bloqueante_callback.cpp`](ej02_no_bloqueante_callback.cpp) | `read_async` lanza un `std::thread` que hace el `sleep` y luego invoca un **callback**; la función **retorna al instante** respecto del hilo del `main`. Incluye `detach()` y un `sleep` extra en `main` para no matar el proceso antes del callback. |
| [`ej04_without_co_routines.cpp`](ej04_without_co_routines.cpp) | Mismo patrón callback + hilo, pero con **varios pasos encadenados** (leer → transformar → guardar): el flujo asíncrono se ve como **callbacks anidados**. |
| [`ej04_co_routines.cpp`](ej04_co_routines.cpp) | El mismo encadenamiento expresado con **`co_await`**: el código se lee **en orden**, como un programa secuencial, aunque por debajo siga habiendo esperas y otro hilo. |

### Ideas para remarcar en clase

**Ej01 — bloqueante**

- El hilo queda ocupado en la espera: no puede hacer otro trabajo útil en ese modelo secuencial.
- Si cada operación bloqueara así y quisieras mucha concurrencia “al mismo tiempo”, el modelo empuja a **muchos hilos** (costo de memoria y de planificación del SO).

**Ej02 — callback (no bloqueante para el llamador)**

- Quien llama a `read_async` **no** espera al disco en esa llamada; puede imprimir “Doing other work…” de inmediato.
- **No es magia:** igual hay un hilo del sistema en el que ocurre la espera; cambia **qué** hilo bloquea.
- `detach()` implica cuidar el **ciclo de vida** del proceso (acá se duerme `main` a propósito). En código real suele haber `join`, un bucle de eventos, o abstracciones como `std::future` / APIs async del framework.

### `ej02_no_bloqueante_callback.cpp`: qué hace el cuerpo de `read_async`

En las líneas 22–29, `read_async` **no** hace el `sleep` en el hilo que la invocó. Crea un `std::thread` con una **lambda** que:

1. Copia/mueve el `callback` al closure (`cb`) para usarlo dentro del hilo nuevo.
2. En ese hilo nuevo, llama a `std::this_thread::sleep_for(2s)` (simula I/O lento).
3. Cuando termina, ejecuta `cb("data from disk")`: ahí recién corre tu lógica de “ya tengo los datos”.

Mientras tanto, `read_async` ya **terminó** y el hilo del `main` siguió. El `detach()` suelta el hilo del `std::thread` (no hace `join` en el llamador): por eso el programa debe vivir lo suficiente para que el callback se ejecute (en el ejemplo, `main` duerme 3 s a propósito).

---

## `ej04_without_co_routines.cpp`: rutinas encadenadas de forma asíncronica

Acá el flujo es **leer datos → transformar → guardar**, y cada paso es **lento** (otro `sleep` en otro hilo) y termina llamando a un **callback** con el resultado del paso.

- **`read_async`**: cuando “termina la lectura”, llama al callback con un `std::string`.
- **`transform`**: recibe ese string y, en **otro** `thread`, después de esperar, llama al callback con el string transformado.
- **`save`**: recibe el resultado final y, en otro hilo, al terminar llama al callback sin argumentos (solo “listo”).

En `main`, el encadenamiento se escribe **anidando lambdas**:

```cpp
read_async([](std::string data) {
    transform(data, [](std::string result) {
        save(result, []() {
            std::cout << "done\n";
        });
    });
});
```

Eso es **asíncrono** porque ninguna de esas funciones “espera” en el sentido de bloquear al hilo del `main` en la llamada: cada una lanza trabajo en segundo plano y **más tarde** se dispara el siguiente paso. El orden lógico (leer, luego transformar, luego guardar) está garantizado por **quién llama a quién** en cada callback, no porque el código se lea de arriba a abajo como un solo bloque.

El costo didáctico es el famoso **“callback hell”**: muchos niveles de indentación, difícil de leer y de depurar cuando el flujo crece. Sirve para ver **por qué** más adelante conviene otra abstracción (futures, `async`, o corrutinas).

---

## `ej04_co_routines.cpp`: para qué sirven las corrutinas acá

Las **corrutinas** en C++20 permiten escribir código que **se puede suspender** y **reanudar** sin bloquear el hilo del llamador de la misma forma que un `sleep` largo en línea recta. Con `co_await` decís: “en este punto espero a que termine esta operación asíncrona; cuando esté lista, **seguí desde acá**”.

En este ejemplo, `workflow()` es una corrutina que se lee **como un programa secuencial**:

```cpp
auto data = co_await read_async();
auto result = co_await transform(data);
co_await save(result);
std::cout << "done\n";
```

**Para qué sirve (idea clave):** expresar el **mismo encadenamiento** que en `ej04_without_co_routines.cpp`, pero con **menos anidación** y un orden visual claro: primero `data`, después `result`, después guardar. El compilador y el tipo `Task` / `AsyncOp` se encargan de que, al “esperar”, la corrutina se suspenda y otro mecanismo (acá un `std::thread` en `await_suspend` que hace `h.resume()`) complete el paso.

No reemplazan solas a los hilos: en este repo, **debajo** sigue habiendo hilos para simular I/O. Lo que cambia es **cómo escribís y leés** el flujo: más parecido a código síncrono, con menos callbacks explícitos anidados. En proyectos reales, las librerías (red, archivos, etc.) suelen ofrecer operaciones “awaitables” parecidas en espíritu a `AsyncOp`.

---

## Cómo compilar

Desde esta carpeta (`Info2-Cpp-Thread-Adv`). Con **g++**, los hilos suelen requerir **`-pthread`**:

```bash
g++ -std=c++20 -O2 -pthread -o ej01_bloqueante   ej01_bloqueante_simulacion_io.cpp
g++ -std=c++20 -O2 -pthread -o ej02_callback     ej02_no_bloqueante_callback.cpp
g++ -std=c++20 -O2 -pthread -o ej04_callbacks    ej04_without_co_routines.cpp
g++ -std=c++20 -O2 -pthread -o ej04_coroutines   ej04_co_routines.cpp
```

**Ejecutar:** Linux/macOS `./ej01_bloqueante`; Windows `ej01_bloqueante.exe` (o el nombre que hayas puesto tras `-o`).

**MSVC:** compilá con `/std:c++20` (y las opciones habituales de tu entorno para enlazar el runtime de hilos si hiciera falta).

---

## Siguiente paso (mismo tema, otra abstracción)

Para el mismo tipo de problema sin `detach` “a ciegas”, en el repo **Info2-Cpp-Async** hay ejemplos con `std::async`, `std::future` / `std::promise` y un pool mínimo. Ver el [`readme.md`](../Info2-Cpp-Async/readme.md) de ese directorio.
