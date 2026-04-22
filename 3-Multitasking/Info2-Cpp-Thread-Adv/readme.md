# Hilos y I/O: bloqueante vs no bloqueante (sin corrutinas)

Este directorio complementa la charla sobre **qué hilo está esperando**. Los ejemplos usan **C++20** (`std::chrono_literals`, `[[nodiscard]]`, etc.) pero **no** usan corrutinas (`co_await`): el foco es comparar un flujo **secuencial que bloquea** con un patrón **callback + otro hilo** donde el llamador no espera en la llamada.

La “lectura de disco” se simula con `std::this_thread::sleep_for`: es solo didáctica; en un programa real el bloqueo vendría del sistema operativo o de una API de I/O.

---

## Ejemplos

| Archivo | Qué muestra |
|---------|-------------|
| [`ej01_bloqueante_simulacion_io.cpp`](ej01_bloqueante_simulacion_io.cpp) | `read_from_disk()` hace el `sleep` en el **mismo** hilo que llama: el flujo no sigue hasta que termina la operación lenta. Se mide el tiempo total con `steady_clock`. |
| [`ej02_no_bloqueante_callback.cpp`](ej02_no_bloqueante_callback.cpp) | `read_async` lanza un `std::thread` que hace el `sleep` y luego invoca un **callback**; la función **retorna al instante** respecto del hilo del `main`. Incluye `detach()` y un `sleep` extra en `main` para no matar el proceso antes del callback. |

### Ideas para remarcar en clase

**Ej01 — bloqueante**

- El hilo queda ocupado en la espera: no puede hacer otro trabajo útil en ese modelo secuencial.
- Si cada operación bloqueara así y quisieras mucha concurrencia “al mismo tiempo”, el modelo empuja a **muchos hilos** (costo de memoria y de planificación del SO).

**Ej02 — callback (no bloqueante para el llamador)**

- Quien llama a `read_async` **no** espera al disco en esa llamada; puede imprimir “Doing other work…” de inmediato.
- **No es magia:** igual hay un hilo del sistema en el que ocurre la espera; cambia **qué** hilo bloquea.
- `detach()` implica cuidar el **ciclo de vida** del proceso (acá se duerme `main` a propósito). En código real suele haber `join`, un bucle de eventos, o abstracciones como `std::future` / APIs async del framework.

---

## Cómo compilar

Desde esta carpeta (`Info2-Cpp-Thread-Adv`). Con **g++**, los hilos suelen requerir **`-pthread`**:

```bash
g++ -std=c++20 -O2 -pthread -o ej01_bloqueante   ej01_bloqueante_simulacion_io.cpp
g++ -std=c++20 -O2 -pthread -o ej02_callback     ej02_no_bloqueante_callback.cpp
```

**Ejecutar:** Linux/macOS `./ej01_bloqueante`; Windows `ej01_bloqueante.exe` (o el nombre que hayas puesto tras `-o`).

**MSVC:** compilá con `/std:c++20` (y las opciones habituales de tu entorno para enlazar el runtime de hilos si hiciera falta).

---

## Siguiente paso (mismo tema, otra abstracción)

Para el mismo tipo de problema sin `detach` “a ciegas”, en el repo **Info2-Cpp-Async** hay ejemplos con `std::async`, `std::future` / `std::promise` y un pool mínimo. Ver el [`readme.md`](../Info2-Cpp-Async/readme.md) de ese directorio.
