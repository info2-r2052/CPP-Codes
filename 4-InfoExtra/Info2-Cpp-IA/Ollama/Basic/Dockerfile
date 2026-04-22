FROM teeks99/boost-cpp-docker:clang-21

RUN apt-get update

RUN apt-get install -y libcpprest-dev g++ 

RUN apt-get install -y libpqxx-dev

# Copiamos el proyecto
COPY . .

# Compilamos el codigo
RUN g++ OllamaExample.cpp -o OllamaExample.e -lcpprest -lboost_system -lboost_thread -lboost_chrono -pthread -lcrypto -lpqxx -lpq

EXPOSE 8080

# Ejecutamos el codigo
CMD ["./OllamaExample.e"]