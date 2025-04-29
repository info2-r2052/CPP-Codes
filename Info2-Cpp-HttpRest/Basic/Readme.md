# Ejemplo de Servicio API REST en C++

Este repositorio contiene un ejemplo de cómo crear un servicio API REST en C++ utilizando C++ REST SDK.

## Descripción del código

El archivo `RestService.cpp` contiene un programa que demuestra la creación de un servicio API REST en C++ utilizando C++ REST SDK. Aquí hay una breve explicación del código:

- Se crea un `http_listener` en la dirección `http://0.0.0.0:8080/test`, que escucha las solicitudes en el puerto 8080 y en el endpoint `/test`.
- Se manejan las solicitudes GET en el endpoint `/test` utilizando una función lambda. En este caso, se crea una respuesta con un cuerpo en formato JSON que contiene información ficticia (nombre, apellido y edad).
- El servicio se inicia llamando al método `open()` del listener y se cierra cuando se recibe una entrada por consola.

## Cómo compilar y ejecutar el código

Para compilar y ejecutar el programa, necesitarás tener instalado C++ REST SDK. Sigue estos pasos:

1. Asegúrate de tener un compilador de C++ instalado en tu sistema.
2. Instala C++ REST SDK siguiendo las instrucciones en su [página oficial](https://github.com/microsoft/cpprestsdk).
3. Coloca el archivo `RestService.cpp` en un directorio.
4. Abre una terminal y navega hasta el directorio que contiene el archivo.
5. Compila el código ejecutando el siguiente comando:

   ```
    g++ -o RestService RestService.cpp -lboost_system -lcrypto -lssl -lcpprest
   ```
6. Una vez compilado, ejecuta el programa con el siguiente comando:

   ```
    ./RestService
   ```


Esto iniciará el servicio y lo dejará escuchando en el puerto 8080.

## Ejemplo de llamada al servicio utilizando cURL

Puedes probar el servicio haciendo una solicitud GET utilizando cURL. Aquí tienes un ejemplo de cómo hacerlo:

```bash
curl -X GET http://localhost:8080/test

Esto debería devolver una respuesta JSON con información ficticia.

## Cómo usar el Dockerfile

Para ejecutar el programa utilizando Docker, sigue estos pasos:

1. Asegúrate de tener Docker instalado en tu sistema.
2. Coloca el archivo `ListExample.cpp` y el Dockerfile en un mismo directorio.
3. Abre una terminal y navega hasta el directorio que contiene los archivos.
4. Construye la imagen del contenedor ejecutando el siguiente comando:

   ```
    docker build -t httprestserver .
   ```

5. Una vez que se complete la construcción de la imagen, puedes ejecutar el programa en un contenedor Docker utilizando el siguiente comando:

    ```
    docker run -it --rm -p 8080:8080 httprestserver
    ```


