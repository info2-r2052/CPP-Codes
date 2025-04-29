FROM debian:11.0-slim

RUN apt-get update

RUN apt-get install -y libcpprest-dev g++

# Copiamos el proyecto
COPY . .

# Compilamos el codigo
RUN g++ -o SmartPointer_1.e SmartPointer_1.cpp -lpthread

# Ejecutamos el codigo
CMD ["./SmartPointer_1.e"]