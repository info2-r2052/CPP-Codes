# Ejemplo2026 — Coordenadas (`Coor`)

Ejemplo de clase en C++ que representa un par de coordenadas enteras `(x, y)` en el plano, con constructores, copia, destructor y métodos de acceso.

## Estructura del código

| Archivo | Rol |
|--------|-----|
| `coordenadas.h` | Declaración de la clase `Coor`: miembros privados, prototipos de métodos e *include guard* para evitar inclusiones múltiples. |
| `coordenadas.cpp` | Implementación de los métodos: constructores, destructor, `Suma`, `Print`, *getters* y *setters*. |
| `main.cpp` | Programa que crea varios objetos `Coor`, prueba la copia y llama a `Print()` sobre uno de ellos. |

### Clase `Coor`

- **Miembros privados:** `x`, `y` (coordenadas) y un `std::string pass` con valor por defecto (ejemplo de dato adicional).
- **Constructores:**
  - Por defecto: inicializa `(0, 0)`.
  - `(int, int)` y `(float, int)`: fijan `x` e `y` (en el caso `float`, se convierte `x` a entero).
  - Copia: `Coor(const Coor &)` — construye un objeto a partir de otro.
- **Destructor:** vacío; existe para poder extender la clase más adelante si hace falta liberar recursos.
- **`Suma`:** recibe dos `Coor` por valor, devuelve un nuevo `Coor` cuyas coordenadas son la suma componente a componente.
- **`Print`:** muestra por consola `x` e `y`.
- **`getX` / `getY` / `setX` / `setY`:** lectura y escritura de las coordenadas.

En `main.cpp`, el flujo típico crea `A`, `B`, `C` y una copia `D` a partir de `A`, e imprime las coordenadas de `A`. El uso de `Suma` y la impresión directa de `C` pueden estar comentados según la versión del archivo.

## Compilación

Desde esta carpeta (`Ejemplo2026`), en **Git Bash**, **MSYS2 MinGW** o cualquier terminal donde `g++` sea el compilador de MinGW:

```bash
g++ main.cpp coordenadas.cpp -o coor.e -std=c++23 -static-libgcc -static-libstdc++
```

Eso genera el ejecutable `coor.e`. Para ejecutarlo:

```bash
./coor.e
```

En **PowerShell** o **cmd** (Windows), desde la misma carpeta:

```powershell
g++ main.cpp coordenadas.cpp -o coor.e -static-libgcc -static-libstdc++
.\coor.e
```

### ¿Para qué sirven `-static-libgcc` y `-static-libstdc++`?

Por defecto, MinGW suele **enlazar de forma dinámica** contra:

- **libgcc:** runtime de GCC (excepciones, soporte de bajo nivel del compilador, etc.).
- **libstdc++:** biblioteca estándar de C++ (`std::string`, `std::cout`, contenedores, etc.).

Esas partes se cargan desde DLLs (`libgcc_*.dll`, `libstdc++-6.dll`, etc.) en tiempo de ejecución. Si en el **PATH** del sistema hay **otra versión** de esas DLLs (otro MinGW, instalaciones viejas, etc.), el programa puede fallar al arrancar o dar errores raros (por ejemplo *segmentation fault* al usar `std::cout`).

Las opciones hacen lo siguiente:

| Opción | Efecto |
|--------|--------|
| **`-static-libgcc`** | Enlaza **estáticamente** la parte de **libgcc** que corresponde al enlazado; el ejecutable depende menos de una `libgcc` en DLL ajena al toolchain con el que compilaste. |
| **`-static-libstdc++`** | Enlaza **estáticamente** **libstdc++**; las rutinas de la biblioteca estándar de C++ van dentro del `.exe` (más tamaño en disco) y **no** hace falta que en la máquina exista la `libstdc++-6.dll` “correcta” en el PATH. |

**Resumen:** no son obligatorias para que el código compile, pero en Windows con varios MinGW o PATH sucio suelen **evitar conflictos de DLLs** y hacer el binario más **portable** entre carpetas y PCs, a costa de un ejecutable algo más grande.

---

*Informática II — ejemplo de clases y coordenadas.*
