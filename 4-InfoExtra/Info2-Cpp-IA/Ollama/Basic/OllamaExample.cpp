#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/http_client.h> 
#include <cpprest/json.h>
#include <unordered_map>
#include <mutex>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;

int main() {
    try {
        // Crear cliente HTTP para Ollama
        http_client_config config;
        config.set_timeout(std::chrono::seconds(240));

        http_client client(U("http://host.docker.internal:11434/api/generate"), config);

        // Construir JSON para enviar la solicitud
        json::value request;
        request[U("model")] = json::value::string(U("mistral"));
        request[U("prompt")] = json::value::string(U("Responde todo como si fueras Homero Simpson y quiere explicar todo con donas. ¿Qué es un microcontrolador?"));
        request[U("stream")] = json::value::boolean(false);
        request[U("max_tokens")] = json::value::number(50); //Esto limita la cantidad de palabras en la respuesta, haciéndola más rápida.
     
        // Enviar la solicitud POST
        client.request(methods::POST, U(""), request.serialize(), U("application/json"))
        .then([](http_response response) {
            return response.extract_json();
        })
        .then([](json::value responseBody) {
            std::cout << L"Respuesta: " << responseBody[U("response")].as_string() << std::endl;
        })
        .wait();
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
