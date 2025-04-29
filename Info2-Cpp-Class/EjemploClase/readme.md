g++ main.cpp Persona.cpp Alumno.cpp -o test

o

# 📄 Introducción al uso de Makefile en C++

## ¿Qué es un Makefile?

Un `Makefile` es un archivo que permite automatizar la compilación de programas. Es muy útil en proyectos con múltiples archivos `.cpp` y `.h`.

---

## 🎯 ¿Por qué usar Makefile?

- ✅ Evita escribir el comando `g++` completo cada vez.
- ✅ Compila solo los archivos modificados.
- ✅ Ahorra tiempo en proyectos grandes.
- ✅ Permite limpiar fácilmente archivos generados (`.o`, ejecutables).
- ✅ Organiza mejor los proyectos, especialmente en equipo.

---

## 🧱 Estructura básica de un Makefile

```makefile
# Nombre del compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos fuente
SRCS = main.cpp Persona.cpp

# Archivos objeto generados
OBJS = $(SRCS:.cpp=.o)

# Nombre del ejecutable
TARGET = info2

# Regla principal
all: $(TARGET)

# Cómo generar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Cómo compilar cada archivo fuente a objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
```

---

## 🛠️ Cómo usarlo

1. Guardá el archivo como `Makefile` (sin extensión).
2. Abrí una terminal en la carpeta del proyecto.
3. Ejecutá:

```bash
make        # Compila el programa
make clean  # Borra los archivos .o y el ejecutable
```

---

## 🧠 Conceptos clave

| Concepto | Descripción |
|---------|-------------|
| `make` | Busca un archivo llamado `Makefile` y ejecuta la primera regla (`all`) |
| `.o` | Archivos objeto intermedios que se enlazan para crear el ejecutable |
| `-c` | Compila sin enlazar |
| `-o` | Indica el nombre del archivo de salida |
| `clean` | Regla especial para borrar archivos generados |

---

## 📌 ¿Cuándo conviene usar Makefile?

| Situación                          | ¿Usar Makefile? |
|-----------------------------------|------------------|
| Proyecto simple con 1 archivo     | ❌ No necesario   |
| Proyecto con varios `.cpp`/`.h`   | ✅ Muy útil       |
| Proyecto compartido en grupo      | ✅ Recomendado    |
| Querés ahorrar tiempo compilando  | ✅ Ideal          |

