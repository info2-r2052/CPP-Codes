## 1. Introducción a la POO en C++  

La **Programación Orientada a Objetos (POO)** es un paradigma que organiza el código en torno a **objetos**, los cuales tienen **atributos (datos)** y **métodos (funciones)**. Esto facilita la **modularidad**, **reutilización** y **mantenimiento** del código.  

Una buena analogía para entenderlo es pensar en una "receta de cocina" (clase) que define los ingredientes (atributos) y pasos a seguir (métodos). A partir de esa receta, podemos hacer varios platillos (objetos) con pequeñas variaciones. Otra analogía útil es pensar en un "molde para hacer galletas". El molde (clase) define la forma y características de la galleta (objeto), pero cada galleta puede tener diferentes decoraciones o ingredientes adicionales sin cambiar el molde base.  

## 2. Concepto de Clase y Objeto  

Una **clase** es una plantilla o molde que define un **objeto**. Contiene:  

- **Atributos**: Representan los datos (variables).  
- **Métodos**: Son funciones que operan sobre los datos.  

Un **objeto** es una instancia de una clase, que almacena datos y puede ejecutar las funciones definidas en la clase.  

### Ejemplo de Clase en C++  

```cpp
#include <iostream>
using namespace std;

// Definimos la clase "Coche"
class Coche {
private:
    string marca;
    int velocidad;

public:
    // Constructor
    Coche(string m, int v) {
        marca = m;
        velocidad = v;
    }

    // Método para mostrar datos
    void mostrarInfo() {
        cout << "Marca: " << marca << ", Velocidad: " << velocidad << " km/h" << endl;
    }
};

int main() {
    Coche miCoche("Toyota", 120);
    miCoche.mostrarInfo();
    return 0;
}
```

### Salida esperada:  

```
Marca: Toyota, Velocidad: 120 km/h
```  

## 3. Ventajas de la POO en C++  

- **Modularidad**: Organiza el código en unidades reutilizables.  
- **Encapsulamiento**: Protege los datos mediante modificadores de acceso (`private`, `public`).  
- **Reutilización**: Podemos crear nuevos objetos sin repetir código.  
- **Facilidad de mantenimiento**: Es más fácil corregir errores y hacer mejoras.  

## 4. Conceptos Claves en POO  

| Concepto            | Descripción                                               | Ejemplo                             |
| ------------------- | --------------------------------------------------------- | ----------------------------------- |
| **Clase**           | Plantilla para crear objetos                              | `class Coche { ... };`              |
| **Objeto**          | Instancia de una clase                                    | `Coche miCoche;`                    |
| **Encapsulamiento** | Oculta detalles internos y protege datos                  | `private:`                          |

## 5. Miembros Públicos, Privados y Protegidos  

En C++, los **modificadores de acceso** determinan la visibilidad de los atributos y métodos dentro de una clase. Existen tres niveles de acceso:  

- **`public`**: Los miembros públicos pueden ser accedidos desde fuera de la clase.  
- **`private`**: Los miembros privados solo pueden ser accedidos dentro de la propia clase.  
- **`protected`**: Similar a `private`, pero las clases derivadas pueden acceder a estos miembros.  

### Ejemplo de Modificadores de Acceso  

```cpp
#include <iostream>
using namespace std;

class Persona {
private:
    string nombre;  // Solo accesible dentro de la clase

protected:
    int edad;  // Accesible en clases derivadas

public:
    void setNombre(string n) {  // Método público para modificar nombre
        nombre = n;
    }

    string getNombre() {  // Método público para obtener nombre
        return nombre;
    }
};

class Empleado : public Persona {
public:
    void setEdad(int e) {
        edad = e;  // Se puede acceder porque es "protected"
    }

    void mostrarDatos() {
        cout << "Nombre: " << getNombre() << ", Edad: " << edad << endl;
    }
};

int main() {
    Empleado emp;
    emp.setNombre("Carlos");
    emp.setEdad(30);
    emp.mostrarDatos();  // Nombre: Carlos, Edad: 30

    return 0;
}
```

### Resumen  

| Modificador | Accesible desde la misma clase | Accesible desde clases derivadas | Accesible desde fuera de la clase |
|------------|--------------------------------|--------------------------------|----------------------------------|
| `public`   | Sí                           | Sí                           | Sí                            |
| `protected`| Sí                           | Sí                           | No                            |
| `private`  | Sí                           | No                           | No                            |




