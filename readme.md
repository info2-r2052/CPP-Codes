<h1 align="center">Códigos CPP 2026</h1>
<p align="center">
  <img src="images/Logo.png" alt="Logo del proyecto" width="200">
</p>
<p align="center">
  Este proyecto contiene ejemplos de código en C++ orientados a prácticas modernas,<br>
  organización de archivos, y documentación profesional.<br>
  ¡Todo listo para brillar en 2026!
</p>

---

## Para quién es este repositorio

Está pensado para todos los que están aprendiendo C++. No hace falta ser experto en Git: abajo tenés dos formas de bajar el material, con y sin Git.

---

## Cómo bajar o clonar el repositorio

### Opción 1: Descargar ZIP (no necesitás Git)

Ideal si recién empezás o no querés instalar Git todavía.

1. Abrí el repositorio en GitHub: [https://github.com/info2-r2052/CPP-Codes](https://github.com/info2-r2052/CPP-Codes)
2. Hacé clic en el botón verde **Code** (o **<> Code**).
3. Elegí **Download ZIP**.
4. Descomprimí el archivo en la carpeta que quieras y abrí el proyecto con tu editor (por ejemplo Visual Studio Code).

Así tenés una **copia estática** de los archivos. Si el docente actualiza el repo, tendrás que volver a descargar el ZIP para ver los cambios.

### Opción 2: Clonar con Git (recomendado si vas a seguir el curso)

**Git** es una herramienta que guarda el historial de cambios y te permite actualizar el código con un solo comando.

1. Instalá [Git para Windows](https://git-scm.com/download/win) (o el paquete que use tu distro en Linux).
2. Abrí una terminal (en Windows: **PowerShell** o **Git Bash**).
3. Entrá a la carpeta donde guardás los trabajos de la facultad, por ejemplo:

   ```bash
   cd ruta/donde/guardas/tus/repos
   ```

4. Cloná el repositorio (copia local enlazada al servidor):

   ```bash
   git clone https://github.com/info2-r2052/CPP-Codes.git
   ```

5. Entrá a la carpeta del proyecto:

   ```bash
   cd CPP-Codes
   ```

**Comandos útiles más adelante** (cuando ya tengas el repo clonado):

- `git pull` — trae los últimos cambios del servidor (actualizá antes de una clase o práctica).
- `git status` — muestra si modificaste archivos.

Si algo falla, revisá que Git esté instalado (`git --version`) y que tengas conexión a internet.

---

## Organización del directorio

El proyecto está ordenado por **temas**, de lo más básico a temas más avanzados. Cada subcarpeta suele ser un **mini-proyecto** o conjunto de ejemplos sobre un tema.

| Carpeta | Contenido |
|--------|-----------|
| **1-Conceptos_Basicos** | Sintaxis y OOP: clases, herencia, punteros inteligentes, sobrecarga de funciones y operadores, ejemplos introductorios. |
| **2-Libreria_STL** | Contenedores y algoritmos de la biblioteca estándar: listas, vectores, sets, etc. |
| **3-Multitasking** | Concurrencia: hilos básicos y avanzados, lambdas, `async`, promesas, corrutinas (según el ejemplo). |
| **4-InfoExtra** | Temas complementarios: sockets, HTTP/REST, visión por computadora (OpenCV), IA, etc. |
| **images** | Recursos gráficos del propio repositorio (por ejemplo el logo). |
| **.vscode** | Configuración opcional para Visual Studio Code (compilación, depuración). Si usás VS Code, puede ayudarte a compilar sin armar todo a mano. |

### Subcarpetas por tema (referencia rápida)

- **1-Conceptos_Basicos:** `Info2-Cpp-Basic`, `Info2-Cpp-Class`, `Info2-Cpp-Herencia`, `Info2-Cpp-SmartPointers`, `Info2-Cpp-SobrecargaFunciones`, `Info2-Cpp-SobrecargaOperadores`
- **2-Libreria_STL:** `Info2-Cpp-List`, `Info2-Cpp-SetVector`, `Info2-Cpp-Vector`
- **3-Multitasking:** `Info2-Cpp-Thread-Basic`, `Info2-Cpp-Thread-Adv`, `Info2-Cpp-Lambda`, `Info2-Cpp-Async`
- **4-InfoExtra:** `Info2-Cpp-Sockets`, `Info2-Cpp-HttpRest`, `Info2-Cpp-IA`, `Info2-OpenCV`

Dentro de cada subcarpeta podés encontrar archivos `.cpp`, `.h`, un `readme.md` o `README.md` propio del ejemplo, y a veces un `CMakeLists.txt` u otro archivo de build, según el caso.

**Consejo:** empezá por **1-Conceptos_Basicos** y seguí el orden numérico cuando el programa de la materia lo permita; los ejemplos de **3-Multitasking** suelen pedir ya tener claros clases, punteros y STL.
