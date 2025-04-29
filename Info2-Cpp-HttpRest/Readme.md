## C++ REST SDK (cpprestsdk)

### ¿Qué es cpprestsdk?
C++ REST SDK (`cpprestsdk`) es una biblioteca desarrollada por Microsoft para facilitar la construcción de aplicaciones cliente-servidor basadas en REST utilizando C++. Permite realizar solicitudes HTTP, manejar JSON y crear servidores REST de manera eficiente.

### Instalación

#### En Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libcpprest-dev
```

#### En macOS
```bash
brew install cpprestsdk
```

#### En Windows
Se puede instalar usando vcpkg:
```powershell
vcpkg install cpprestsdk
```

### Uso Básico

#### Crear un Servidor REST
```cpp
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

int main() {
    http_listener listener(U("http://localhost:8080/api"));

    listener.support(methods::GET, [](http_request request) {
        json::value response;
        response[U("message")] = json::value::string(U("Hola desde C++ REST SDK"));
        request.reply(status_codes::OK, response);
    });

    listener.open().wait();
    std::cout << "Servidor escuchando en http://localhost:8080/api" << std::endl;
    std::cin.get(); // Mantener el servidor en ejecución
}
```

#### Realizar una Petición HTTP GET
```cpp
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    http_client client(U("http://jsonplaceholder.typicode.com/posts/1"));
    
    client.request(methods::GET).then([](http_response response) {
        if (response.status_code() == status_codes::OK) {
            return response.extract_json();
        }
        return pplx::task_from_result(json::value());
    }).then([](json::value jsonResponse) {
        std::wcout << jsonResponse.serialize() << std::endl;
    }).wait();

    return 0;
}
```

### Clases y Métodos Principales

- `http_listener`: Para crear servidores REST y manejar solicitudes HTTP.
- `http_client`: Para realizar solicitudes HTTP a servidores remotos.
- `json::value`: Para manejar estructuras de datos JSON.
- `methods`: Contiene métodos HTTP comunes (`GET`, `POST`, `PUT`, `DELETE`).
- `status_codes`: Contiene códigos de respuesta HTTP (`OK`, `NotFound`, `BadRequest`, etc.).

Para más información, consulta la documentación oficial: [cpprestsdk en GitHub](https://github.com/microsoft/cpprestsdk).

---
