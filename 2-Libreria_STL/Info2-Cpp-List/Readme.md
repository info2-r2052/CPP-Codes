# Ejemplo de Uso de std::map en C++

Este repositorio contiene un ejemplo de cómo utilizar `std::map` en C++ para almacenar datos en pares clave-valor.

## Explicación del código

El archivo `ListExample.cpp` contiene un programa que demuestra el uso de `std::map` en C++. Aquí hay una breve explicación del código:

- Se utiliza un `std::map<std::string, std::string>` para almacenar valores de tipo `std::string` asociados a claves de tipo `std::string`.
- Se insertan varios pares clave-valor en el mapa utilizando la función `insert`, cada uno con una clave única.
- Se recorre el mapa utilizando un bucle `for` y se imprimen los valores asociados a cada clave.

## Explicación del Dockerfile

El Dockerfile proporcionado se encarga de construir un contenedor Docker que ejecuta el código C++ dentro de un entorno controlado. Aquí hay una explicación de cada instrucción:

- `FROM debian:11.0-slim`: Utiliza la imagen base de Debian 11.0.
- `RUN apt-get update` y `RUN apt-get install -y libcpprest-dev g++`: Actualiza los paquetes disponibles e instala las dependencias necesarias para compilar el código C++.
- `COPY . .`: Copia todos los archivos del directorio actual al directorio de trabajo del contenedor.
- `RUN g++ ListExample.cpp -o ListExample.e`: Compila el archivo `ListExample.cpp` y genera un ejecutable llamado `ListExample.e` utilizando el compilador GCC.
- `CMD ["./ListExample.e"]`: Establece el comando predeterminado que se ejecutará cuando se inicie el contenedor. En este caso, ejecuta el ejecutable generado `ListExample.e`.

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