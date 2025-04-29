# 📌 **Sobrecarga de Operadores en C++**

En C++, la **sobrecarga de operadores** permite redefinir el comportamiento de operadores estándar (`+`, `-`, `*`, `=`...) para que funcionen con tipos de datos personalizados (como clases y estructuras).

---

## 🔹 **¿Qué es la sobrecarga de operadores?**

Es la capacidad de redefinir el comportamiento de un operador cuando se usa con objetos de una clase. Se logra definiendo funciones con el nombre `operatorX`, donde `X` es el operador a sobrecargar.

---

## ✍ **Sintaxis General**
```cpp
class Clase {
public:
    Tipo operatorX(const Clase& otro) {
        // Código que redefine el operador
    }
};
```

### ✅ Ejemplo con `+`:
```cpp
class Coordenada {
private:
    int x, y;
public:
    Coordenada(int a, int b) : x(a), y(b) {}

    // Sobrecarga del operador +
    Coordenada operator+(const Coordenada& otra) {
        return Coordenada(x + otra.x, y + otra.y);
    }
};
```

---

## 🔹 **Tipos de Sobrecarga**

### ✅ 1. Operadores binarios (`+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`, `&`, `|`, `^`, `<<`, `>>`, `=`)
```cpp
Clase operator+(const Clase& otra);
Clase operator*(const Clase& otra);
bool operator==(const Clase& otra) const;
```

### ✅ 2. Operadores unarios (`+`, `-`, `!`, `~`, `++`, `--`)
```cpp
Clase operator-() const;      // Negación unaria
Clase& operator++();          // Prefijo
Clase operator++(int);        // Sufijo
```

### ✅ 3. Operadores de asignación compuesta (`+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`)
```cpp
Clase& operator+=(const Clase& otra);
```

### ✅ 4. Operador de subíndice (`[]`)
```cpp
Tipo& operator[](int index);
```

### ✅ 5. Operador de función (`()`)
Permite que un objeto se use como una función.
```cpp
Tipo operator()(parametros);
```

### ✅ 6. Operador de acceso a miembro (`->`)
```cpp
Clase* operator->();
```

### ✅ 7. Operadores de entrada/salida (`<<`, `>>`)
Deben ser definidos como funciones **friend**.
```cpp
friend std::ostream& operator<<(std::ostream& os, const Clase& obj);
friend std::istream& operator>>(std::istream& is, Clase& obj);
```

---

## 🚫 **Operadores que *no* se pueden sobrecargar**
| Operador | Motivo |
|----------|--------|
| `::`     | Ámbito |
| `.`      | Acceso directo a miembros |
| `.*`     | Acceso a puntero a miembro |
| `sizeof`| Evaluado en tiempo de compilación |
| `typeid`| RTTI |
| `alignof`, `noexcept`, `static_cast`, `dynamic_cast`, etc. | Propios del lenguaje |

---

## 🔹 **Reglas Importantes**
- ✅ Se pueden sobrecargar la mayoría de los operadores.
- 🔒 Algunos operadores (como `=`, `[]`, `->`, `()`) **solo se pueden sobrecargar como métodos miembros**.
- 📌 Si la operación **no modifica el objeto**, marcala como `const`.
- ✅ La sobrecarga puede hacerse como **función miembro** o **función global `friend`**.

---

## 🎯 **Ejemplo Completo**
```cpp
#include <iostream>

class Coordenada {
private:
    int x, y;
public:
    Coordenada(int a = 0, int b = 0) : x(a), y(b) {}

    Coordenada operator+(const Coordenada& otra) const {
        return Coordenada(x + otra.x, y + otra.y);
    }

    Coordenada operator-() const {
        return Coordenada(-x, -y);
    }

    bool operator==(const Coordenada& otra) const {
        return x == otra.x && y == otra.y;
    }

    friend std::ostream& operator<<(std::ostream& out, const Coordenada& c) {
        out << "(" << c.x << ", " << c.y << ")";
        return out;
    }
};

int main() {
    Coordenada A(3, 5), B(1, 2);
    Coordenada C = A + B;

    std::cout << "Suma: " << C << std::endl;
    std::cout << "Negativo: " << -C << std::endl;
    std::cout << "¿A y B son iguales? " << (A == B ? "Sí" : "No") << std::endl;
}
```

📌 **Salida:**
```
Suma: (4, 7)
Negativo: (-4, -7)
¿A y B son iguales? No
```

