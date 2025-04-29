#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

char Html[] = 
"<!DOCTYPE html>"
"<html><body>"
"<h1>Pagina de pruebas de Info 2 &#128512</h1>"
"<h2>Formulario de Usuario</h2>"
"<form action=\"\" method=\"POST\">"
"  <label for=\"fname\">Nombre:</label><br>"
"  <input type=\"text\" id=\"fname\" name=\"fname\" value=\"John\"><br>"
"  <label for=\"lname\">Apellido:</label><br>"
"  <input type=\"text\" id=\"lname\" name=\"lname\" value=\"Doe\"><br><br>"
"  <input type=\"submit\" value=\"Enviar\">"
"</form>"
"</body></html>";

void handle_request(http_request request) {
    std::cout << "Nueva solicitud recibida: " << request.method() << " " << request.relative_uri().to_string() << std::endl;

    if (request.method() == methods::GET) {
        // Enviar el formulario HTML
        request.reply(status_codes::OK, Html, "text/html");
    } 
    else if (request.method() == methods::POST) {
        // Leer los datos enviados por el formulario
        request.extract_string().then([=](std::string body) {
            std::cout << "Datos recibidos: " << body << std::endl;

            // Responder confirmación al cliente
            request.reply(status_codes::OK, "Datos recibidos correctamente.");
        }).wait();
    } 
    else {
        request.reply(status_codes::MethodNotAllowed, "Método no permitido.");
    }
}

int main() {
    http_listener listener(U("http://0.0.0.0:8080"));

    // Manejar solicitudes GET
    listener.support(handle_request);

    try {
        listener.open().wait();
        std::cout << "Servidor escuchando en http://0.0.0.0:8080\n";
        
        std::cin.get(); // Espera a que el usuario presione ENTER
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
