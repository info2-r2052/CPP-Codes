#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <pqxx/pqxx>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

const std::string DB_CONNECTION = "dbname=mydb user=root password=mypassword host=host.docker.internal port=5432";

// Función para ejecutar una consulta en PostgreSQL
pqxx::result execute_query(const std::string& query) {
    pqxx::connection conn(DB_CONNECTION);
    pqxx::work txn(conn);
    pqxx::result res = txn.exec(query);
    txn.commit();
    return res;
}

// Obtener todos los usuarios
void handle_get(http_request request) {
    json::value response;
    try {
        pqxx::result res = execute_query("SELECT id, nombre, apellido, juegos FROM users;");
        for (const auto& row : res) {
            json::value user;
            user[U("id")] = json::value::number(row["id"].as<int>());
            user[U("nombre")] = json::value::string(row["nombre"].as<std::string>());
            user[U("apellido")] = json::value::string(row["apellido"].as<std::string>());
            user[U("juegos")] = json::value::parse(row["juegos"].as<std::string>());
            response[std::to_string(row["id"].as<int>())] = user;
        }
    } catch (const std::exception& e) {
        request.reply(status_codes::InternalError, e.what());
        return;
    }
    request.reply(status_codes::OK, response);
}

// Crear un usuario
void handle_post(http_request request) {
    request.extract_json().then([request](json::value body) {
        try {
            // Verifica si el request es correcto
            if (!body.has_field(U("nombre")) || !body.has_field(U("apellido")) || !body.has_field(U("juegos"))) {
                request.reply(status_codes::BadRequest, U("Missing fields"));
                return;
            }

            // Cargo datos con el request
            std::string nombre = body[U("nombre")].as_string();
            std::string apellido = body[U("apellido")].as_string();
            std::string juegos_json = body[U("juegos")].serialize();
            
            // Genero la query para postgreSQL
            std::string query = "INSERT INTO users (nombre, apellido, juegos) VALUES ($1, $2, $3) RETURNING id;";
            pqxx::connection conn(DB_CONNECTION);
            pqxx::work txn(conn);
            pqxx::result res = txn.exec_params(query, nombre, apellido, juegos_json);
            txn.commit();
            
            // Genero la respuesta del endpoint
            json::value response;
            response[U("id")] = json::value::number(res[0]["id"].as<int>());
            request.reply(status_codes::Created, response);
        } catch (const std::exception& e) {
            request.reply(status_codes::InternalError, e.what());
        }
    }).wait();
}

// Modificar un usuario
void handle_put(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    if (path.empty()) {
        request.reply(status_codes::BadRequest, U("Invalid ID"));
        return;
    }
    int user_id = std::stoi(path[0]);
    
    request.extract_json().then([request, user_id](json::value body) {
        try {
            if (!body.has_field(U("nombre")) || !body.has_field(U("apellido")) || !body.has_field(U("juegos"))) {
                request.reply(status_codes::BadRequest, U("Missing fields"));
                return;
            }
            std::string nombre = body[U("nombre")].as_string();
            std::string apellido = body[U("apellido")].as_string();
            std::string juegos_json = body[U("juegos")].serialize();
            
            std::string query = "UPDATE users SET nombre=$1, apellido=$2, juegos=$3 WHERE id=$4;";
            pqxx::connection conn(DB_CONNECTION);
            pqxx::work txn(conn);
            txn.exec_params(query, nombre, apellido, juegos_json, user_id);
            txn.commit();
            request.reply(status_codes::OK, U("User updated"));
        } catch (const std::exception& e) {
            request.reply(status_codes::InternalError, e.what());
        }
    }).wait();
}

// Eliminar un usuario
void handle_delete(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    if (path.empty()) {
        request.reply(status_codes::BadRequest, U("Invalid ID"));
        return;
    }
    int user_id = std::stoi(path[0]);
    
    try {
        std::string query = "DELETE FROM users WHERE id=$1;";
        pqxx::connection conn(DB_CONNECTION);
        pqxx::work txn(conn);
        txn.exec_params(query, user_id);
        txn.commit();
        request.reply(status_codes::OK, U("User deleted"));
    } catch (const std::exception& e) {
        request.reply(status_codes::InternalError, e.what());
    }
}

int main() {
    http_listener listener(U("http://0.0.0.0:8080/users"));

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::PUT, handle_put);
    listener.support(methods::DEL, handle_delete);

    try {
        listener.open().wait();
        std::cout << "Server running on port 8080...\nPress Enter to stop.\n";
        std::cin.get();
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
