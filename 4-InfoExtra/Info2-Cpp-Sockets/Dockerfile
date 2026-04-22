FROM debian:11.0-slim

RUN apt-get update

RUN apt-get install -y libcpprest-dev g++

# Copiamos el proyecto
COPY . .

# Compilamos el codigo
RUN g++ Info2-HttpServer-Moderm.cpp -o Info2-HttpServer-Moderm.e -lcpprest -lboost_system -lboost_thread -lboost_chrono -pthread -lcrypto

EXPOSE 8080

# Ejecutamos el codigo
CMD ["./Info2-HttpServer-Moderm.e"]