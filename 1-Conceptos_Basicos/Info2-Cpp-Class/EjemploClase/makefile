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