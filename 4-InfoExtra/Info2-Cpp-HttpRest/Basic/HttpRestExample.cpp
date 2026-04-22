#include <iostream>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <unordered_map>
#include <mutex>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

std::unordered_map<int, json::value> users;
std::mutex users_mutex;
int current_id = 1;

void handle_get(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    
    if (path.empty()) {
        json::value response;
        std::lock_guard<std::mutex> lock(users_mutex);
        for (const auto& user : users) {
            response[std::to_string(user.first)] = user.second;
        }
        request.reply(status_codes::OK, response);
    } else {
        int user_id = std::stoi(path[0]);
        std::lock_guard<std::mutex> lock(users_mutex);
        if (users.find(user_id) != users.end()) {
            request.reply(status_codes::OK, users[user_id]);
        } else {
            request.reply(status_codes::NotFound, U("User not found"));
        }
    }
}

void handle_post(http_request request) {
    request.extract_json().then([request](json::value body) {
        if (body.has_field(U("nombre")) && body.has_field(U("apellido")) && body.has_field(U("juegos"))) {
            std::lock_guard<std::mutex> lock(users_mutex);
            int user_id = current_id++;
            users[user_id] = body;
            users[user_id][U("id")] = json::value(user_id);
            request.reply(status_codes::Created, users[user_id]);
        } else {
            request.reply(status_codes::BadRequest, U("Missing fields"));
        }
    }).wait();
}

void handle_put(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    
    if (!path.empty()) {
        int user_id = std::stoi(path[0]);
        request.extract_json().then([request, user_id](json::value body) {
            std::lock_guard<std::mutex> lock(users_mutex);
            if (users.find(user_id) != users.end()) {
                users[user_id] = body;
                users[user_id][U("id")] = json::value(user_id);
                request.reply(status_codes::OK, users[user_id]);
            } else {
                request.reply(status_codes::NotFound, U("User not found"));
            }
        }).wait();
    } else {
        request.reply(status_codes::BadRequest, U("Invalid ID"));
    }
}

void handle_delete(http_request request) {
    auto path = uri::split_path(uri::decode(request.relative_uri().path()));
    
    if (!path.empty()) {
        int user_id = std::stoi(path[0]);
        std::lock_guard<std::mutex> lock(users_mutex);
        if (users.erase(user_id)) {
            request.reply(status_codes::OK, U("User deleted"));
        } else {
            request.reply(status_codes::NotFound, U("User not found"));
        }
    } else {
        request.reply(status_codes::BadRequest, U("Invalid ID"));
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
        std::cout << "Server is running on port 8080...\nPress Enter to stop.\n";
        std::cin.get();
        listener.close().wait();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
