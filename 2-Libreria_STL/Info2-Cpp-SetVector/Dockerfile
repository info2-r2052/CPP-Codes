FROM debian:11.0-slim

RUN apt-get update

RUN apt-get install -y libcpprest-dev g++

# Copiamos el proyecto
COPY . .

# Compilamos el codigo
RUN g++ SetExample.cpp -o SetExample.e 

# Ejecutamos el codigo
CMD ["./SetExample.e"]