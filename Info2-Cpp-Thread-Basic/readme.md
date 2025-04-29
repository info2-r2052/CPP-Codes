# Uso de Threads en C++

Este repositorio contiene un ejemplo simple de cómo utilizar threads en C++ junto con un Dockerfile para facilitar la ejecución del código.

## Explicación del código

El archivo `thead_basico.cpp` contiene un programa que demuestra el uso de threads en C++. Aquí hay una breve explicación del código:

- Se define una función `funcion_hilo` que será ejecutada por cada hilo creado.
- En la función `main`, se crea un vector de hilos `Hilo` y se ejecuta un bucle para crear 10 hilos, cada uno ejecutando la función `funcion_hilo` con un argumento diferente.
- Finalmente, se espera a que todos los hilos terminen su ejecución utilizando la función `join`.

## Explicación del Dockerfile

El Dockerfile proporcionado se encarga de construir un contenedor Docker que ejecuta el código C++ dentro de un entorno controlado. Aquí hay una explicación de cada instrucción:

- `FROM gcc:4.9`: Utiliza la imagen base de GCC versión 4.9.
- `COPY . .`: Copia todos los archivos del directorio actual al directorio de trabajo del contenedor.
- `RUN gcc -o thead_basico.e thead_basico.cpp -lpthread`: Compila el archivo `thead_basico.cpp` y genera un ejecutable llamado `thead_basico.e` utilizando el compilador GCC. La opción `-lpthread` se utiliza para enlazar la biblioteca pthread, necesaria para el manejo de threads.
- `CMD ["./thead_basico.e"]`: Establece el comando predeterminado que se ejecutará cuando se inicie el contenedor. En este caso, ejecuta el ejecutable generado `thead_basico.e`.

## Cómo usar el Dockerfile

Para ejecutar el programa utilizando Docker, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Coloca el archivo `thead_basico.cpp` y el Dockerfile en un mismo directorio.
3. Abre una terminal y navega hasta el directorio que contiene los archivos.
4. Construye la imagen del contenedor ejecutando el siguiente comando:
   ```
   docker build -t thread_ejemplo .
   ```
5. Una vez que se complete la construcción de la imagen, puedes ejecutar el programa en un contenedor Docker utilizando el siguiente comando:
   ```
   docker run thread_ejemplo
   ```

Esto ejecutará el programa dentro del contenedor Docker y verás la salida en la terminal.

