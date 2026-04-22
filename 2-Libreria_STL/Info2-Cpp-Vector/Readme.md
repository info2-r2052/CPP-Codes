# Ejemplo de Uso de std::vector en C++

Este repositorio contiene un ejemplo de cómo utilizar `std::vector` en C++ para almacenar datos en pares clave-valor.

## Explicación del código

El archivo `VectorExample.cpp` contiene un programa que demuestra el uso de `std::vector` en C++. Aquí hay una breve explicación del código:

- Se crea un `std::vector<std::string>` llamado `vec` para almacenar elementos de tipo `std::string`.
- Se utiliza un bucle `for` para insertar los números del 1 al 6 en el vector utilizando el método `push_back()`.
- Se recorre el vector utilizando un bucle `for` y se imprime cada elemento utilizando el método `at()` para acceder al elemento en la posición especificada.

## Cómo usar el Dockerfile

Para ejecutar el programa utilizando Docker, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Coloca el archivo `ListExample.cpp` y el Dockerfile en un mismo directorio.
3. Abre una terminal y navega hasta el directorio que contiene los archivos.
4. Construye la imagen del contenedor ejecutando el siguiente comando:

   ```
    docker build -t listexample .
   ```

5. Una vez que se complete la construcción de la imagen, puedes ejecutar el programa en un contenedor Docker utilizando el siguiente comando:

   ```
    docker run -it --rm listexample
   ```