# Ollama C++ Client Example

Este repositorio contiene un ejemplo de cómo interactuar con **Ollama**, un servidor de modelos de lenguaje, utilizando C++ y `cpprestsdk` para realizar solicitudes HTTP.

## ¿Qué es Ollama?
Ollama es un servidor local que permite ejecutar modelos de lenguaje como `mistral`, `llama2`, entre otros. Se usa para procesar texto mediante solicitudes HTTP y puede ejecutarse en CPU o GPU para optimizar el rendimiento.

## Instalación de Ollama

1. Descarga e instala Ollama:
   ```sh
   curl -fsSL https://ollama.com/install.sh | sh
   ```

2. Verifica que Ollama esté funcionando:
   ```sh
   ollama --version
   ```

3. Descarga un modelo, por ejemplo `mistral`:
   ```sh
   ollama pull mistral
   ```

4. Inicia el servidor de Ollama:
   ```sh
   ollama serve
   ```

Esto dejará Ollama ejecutándose en `http://localhost:11434`.

##  Usar Ollama de forma independiente

Puedes usar Ollama sin necesidad de código C++, directamente desde la terminal:

- **Modo interactivo (chat con el modelo):**
  ```sh
  ollama run mistral
  ```

- **Ejecutar un prompt único:**
  ```sh
  echo "¿Qué es la inteligencia artificial?" | ollama run mistral
  ```

- **Ver modelos disponibles en el sistema:**
  ```sh
  ollama list
  ```

- **Monitorear el uso de recursos:**
  ```sh
  ollama ps
  ```

---

**Los modelos de lenguaje** como los de **Ollama** (Llama 2, Mistral, Gemma, etc.) tienen diferencias clave en **arquitectura, tamaño, entrenamiento y uso ideal**. Aquí te explico **cómo elegir el mejor para cada caso**.  


## **Principales diferencias entre modelos de Ollama**
### **1. Tamaño y rendimiento**
- Los modelos vienen en versiones **pequeñas (7B)**, **medianas (13B)** y **grandes (65B)**
- **7B** es rápido y consume menos RAM, pero tiene menos capacidad de razonamiento  
- **13B** es un equilibrio entre calidad y rendimiento  
- **65B** es más preciso pero necesita **GPUs potentes**  

| Modelo       | Tamaño  | Uso de RAM aprox. | Velocidad  |
|-------------|---------|-------------------|------------|
| **Llama 2 7B** | 7B  | ~8GB RAM | Rápido |
| **Llama 2 13B** | 13B | ~16GB RAM | Medio |
| **Llama 2 65B** | 65B | +64GB RAM (GPU) | Lento pero más preciso |
| **Mistral 7B** | 7B  | ~8GB RAM | Rápido y optimizado |
| **Gemma 7B** | 7B | ~8GB RAM | Similar a Llama 2 7B |
| **Phi 2** | Pequeño | ~4GB RAM | Muy eficiente en recursos |

**¿Cuál elegir?**
- **Tienes CPU sin GPU potente** ? **Mistral 7B** o **Llama 2 7B**  
- **Quieres mejor calidad, tienes GPU** ? **Llama 2 13B**  
- **Para un servidor potente** ? **Llama 2 65B**  

---

### **2. Tipo de datos y conocimiento**
Cada modelo se entrena con **billones de palabras** de diferentes fuentes:  
**Llama 2**: Datos generales de Internet, artículos, libros, código  
**Mistral**: Similar a Llama 2 pero más optimizado  
**Gemma**: De Google, más preciso en temas científicos  
**Phi 2**: Compacto pero sorprendente en razonamiento  

**¿Cuál elegir?**
- **Para responder preguntas generales** ? **Llama 2 o Mistral**  
- **Para texto técnico / investigación** ? **Gemma**  
- **Para aplicaciones livianas** ? **Phi 2**  

---

### **3. Uso recomendado**
| Modelo         | Mejor para... |
|---------------|--------------|
| **Llama 2**   | Chatbots, generación de texto, asistencia general |
| **Mistral**   | Chatbots rápidos, razonamiento lógico |
| **Gemma**     | Texto técnico y científico |
| **Phi 2**     | Aplicaciones ligeras en dispositivos con poca RAM |

**Ejemplos de uso**  
- *Un bot para responder preguntas generales* => **Llama 2 7B o Mistral 7B**  
- *Un asistente médico o científico* => **Gemma**  
- *Un chatbot en un celular o Raspberry Pi* => **Phi 2**  

---

## **¿Qué información contienen estos modelos?**
Los modelos **no almacenan información específica** como una base de datos, pero han aprendido patrones de texto y conocimiento general de su entrenamiento. **No recuerdan conversaciones pasadas a menos que se implemente un historial en la API.**  

**Ejemplo**  
- *No saben datos en tiempo real* ? No puedes preguntar el clima de hoy  
- *Pero pueden inferir información lógica* ? Explicar qué es la lluvia  

Si necesitas que el modelo acceda a **datos actuales o privados**, debes combinarlo con una **base de datos o API externa**.   

---

## Cómo ejecutar el cliente C++

### Requisitos
- Compilador C++ con soporte para C++17 o superior.
- `cpprestsdk` y `libpqxx` instalados.
- Docker (opcional, para ejecutar en un contenedor).

### Compilar y ejecutar
#### En Linux/Mac:
```sh
g++ OllamaExample.cpp -o OllamaExample -lcpprest -lboost_system -lboost_thread -lboost_chrono -pthread -lcrypto -lpqxx -lpq
./OllamaExample
```

#### En Docker:
1. Construir la imagen:
   ```sh
   docker build -t ollamatest .
   ```
2. Ejecutar el contenedor:
   ```sh
   docker run -it --rm ollamatest
   ```

## Código Explicado
El siguiente código en C++ envía una solicitud HTTP POST a **Ollama**, pidiéndole que genere una respuesta basada en el modelo `mistral`.

```cpp
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    try {
        http_client_config config;
        config.set_timeout(std::chrono::seconds(240));

        http_client client(U("http://localhost:11434/api/generate"), config);

        json::value request;
        request[U("model")] = json::value::string(U("mistral"));
        request[U("prompt")] = json::value::string(U("¿Qué es la inteligencia artificial?"));
        request[U("stream")] = json::value::boolean(false);
        request[U("max_tokens")] = json::value::number(50);

        client.request(methods::POST, U(""), request.serialize(), U("application/json"))
        .then([](http_response response) {
            return response.extract_json();
        })
        .then([](json::value responseBody) {
            std::wcout << L"Respuesta: " << responseBody[U("response")].as_string() << std::endl;
        })
        .wait();
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```

## Explicación del código
1. **Configuración del cliente HTTP:** Se usa `cpprestsdk` para enviar una solicitud HTTP POST a `Ollama`.
2. **Parámetros de la solicitud:**
   - `model`: Especifica el modelo a usar (`mistral`).
   - `prompt`: Pregunta que se enviará al modelo.
   - `stream`: `false` indica que esperamos la respuesta completa.
   - `max_tokens`: Limita la cantidad de palabras generadas.
3. **Procesamiento de la respuesta:** Se extrae el JSON de la respuesta y se muestra en consola.

---






