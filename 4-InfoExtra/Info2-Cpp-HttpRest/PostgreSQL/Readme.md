# Ejemplo de Servicio API REST en C++ con PostgreSQL

Este repositorio contiene un ejemplo de cómo crear un servicio API REST en C++ utilizando C++ REST SDK (cpprestsdk) y PostgreSQL como base de datos.

## Tecnologías Utilizadas

- **C++ REST SDK (cpprestsdk)**: Biblioteca para construir aplicaciones cliente-servidor REST en C++.
- **PostgreSQL**: Base de datos relacional para almacenar y gestionar información de usuarios.
- **Docker**: Utilizado para ejecutar la base de datos PostgreSQL en un contenedor.

## ¿Qué es C++ REST SDK y cuándo usarlo?

C++ REST SDK, también conocido como `cpprestsdk`, es una biblioteca desarrollada por Microsoft para facilitar la creación de aplicaciones cliente-servidor basadas en REST en C++.

Se recomienda utilizar esta biblioteca cuando:
- Se necesita construir APIs REST en C++.
- Se trabaja con clientes que deben consumir servicios REST desde aplicaciones de escritorio o embebidas.
- Se requiere una solución ligera y multiplataforma para la comunicación HTTP.

## Descripción del Código

El archivo `RestService.cpp` contiene la implementación de un servicio API REST que permite gestionar usuarios en una base de datos PostgreSQL.

- Se crea un `http_listener` en la dirección `http://0.0.0.0:8080/users`, que maneja las siguientes solicitudes:
  - **GET /users**: Obtiene la lista de usuarios.
  - **POST /users**: Agrega un nuevo usuario.
  - **PUT /users/{id}**: Modifica un usuario existente.
  - **DELETE /users/{id}**: Elimina un usuario de la base de datos.
- Cada operación accede a PostgreSQL usando `libpqxx`, una biblioteca de C++ para interactuar con PostgreSQL.

## Configuración y Ejecución

### 1. Levantar la Base de Datos con Docker

Para ejecutar PostgreSQL en un contenedor Docker, usa el siguiente comando:

```bash
docker run --name my-postgres -e POSTGRES_DB=mydb -e POSTGRES_USER=root -e POSTGRES_PASSWORD=mypassword -p 5432:5432 -d postgres
```

Esto creará un contenedor PostgreSQL accesible en `localhost:5432`.

### 2. Crear la Tabla Inicial en PostgreSQL

Antes de ejecutar el servicio, es necesario crear la tabla `users`. Puedes hacerlo conectándote a PostgreSQL y ejecutando el siguiente script SQL:

```sql
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    apellido VARCHAR(100) NOT NULL,
    juegos JSONB NOT NULL
);
```

Si tienes `psql` instalado, ejecuta:

```bash
psql -h localhost -U root -d mydb
```
Luego, ingresa el comando SQL anterior para crear la tabla.

También puedes ejecutar el script directamente en DBeaver conectándote a la base de datos y pegando el código en el editor SQL.

### 3. Compilar y Ejecutar el Servicio API REST

#### Requisitos Previos

Asegúrate de tener instaladas las siguientes dependencias:
- Un compilador de C++ (GCC, Clang o MSVC).
- [C++ REST SDK](https://github.com/microsoft/cpprestsdk)
- [libpqxx](https://github.com/jtv/libpqxx) para interactuar con PostgreSQL.

#### Compilación

Compila el código ejecutando:

```bash
g++ -o RestService RestService.cpp -lboost_system -lcrypto -lssl -lcpprest -lpqxx -lpq
```

#### Ejecución

Ejecuta el servicio con:

```bash
./RestService
```

Esto iniciará el servidor y lo dejará escuchando en el puerto `8080`.

### 4. Probar el Servicio con cURL

#### Obtener la lista de usuarios:

```bash
curl -X GET http://localhost:8080/users
```

#### Agregar un usuario:

```bash
curl -X POST http://localhost:8080/users -H "Content-Type: application/json" -d '{"nombre": "Juan", "apellido": "Pérez", "juegos": ["Ajedrez", "Fútbol"]}'
```

#### Modificar un usuario:

```bash
curl -X PUT http://localhost:8080/users/1 -H "Content-Type: application/json" -d '{"nombre": "Juan", "apellido": "Gómez", "juegos": ["Tenis"]}'
```

#### Eliminar un usuario:

```bash
curl -X DELETE http://localhost:8080/users/1
```

## Uso de Docker para Ejecutar el Servicio

Puedes ejecutar el servicio API en un contenedor Docker con los siguientes pasos:

1. Construye la imagen del contenedor:

   ```bash
   docker build -t httprestserver .
   ```

2. Ejecuta el contenedor:

   ```bash
   docker run -it --rm -p 8080:8080 httprestserver
   ```

El servicio estará disponible en `http://localhost:8080/users`.

## Conceptos Clave para Leer y Escribir en PostgreSQL con C++

### Lectura de Datos

1. Establecer una conexión:
   ```cpp
   pqxx::connection conn("dbname=mydb user=root password=mypassword host=localhost port=5432");
   ```

2. Crear una transacción y ejecutar la consulta:
   ```cpp
   pqxx::work txn(conn);
   pqxx::result res = txn.exec("SELECT * FROM users;");
   ```

3. Procesar los resultados:
   ```cpp
   for (const auto& row : res) {
       std::cout << "ID: " << row["id"].as<int>() << " Nombre: " << row["nombre"].as<std::string>() << std::endl;
   }
   ```

4. Confirmar la transacción:
   ```cpp
   txn.commit();
   ```

### Escritura de Datos

1. Crear una transacción:
   ```cpp
   pqxx::work txn(conn);
   ```

2. Ejecutar una consulta con parámetros:
   ```cpp
   txn.exec_params("INSERT INTO users (nombre, apellido, juegos) VALUES ($1, $2, $3);", "Juan", "Pérez", "[\"Ajedrez\", \"Fútbol\"]");
   ```

3. Confirmar los cambios en la base de datos:
   ```cpp
   txn.commit();
   ```



