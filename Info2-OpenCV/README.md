
---

# Proyecto OpenCV

Este repositorio contiene presentaciones y ejemplos prácticos sobre cómo usar OpenCV en diferentes plataformas (Windows, Linux, Docker). OpenCV es una biblioteca de código abierto que proporciona infraestructura para la visión por computadora en tiempo real. Se utiliza en aplicaciones que van desde el procesamiento de imágenes hasta la visión por computadora avanzada.

## ¿Qué es OpenCV?

OpenCV (Open Source Computer Vision Library) es una biblioteca de software diseñada para facilitar la implementación de aplicaciones y tareas de visión por computadora. Incluye miles de algoritmos que cubren diversas áreas, como el procesamiento de imágenes, la detección de objetos y el reconocimiento facial.

- [Sitio web oficial de OpenCV](https://opencv.org/)
- [Repositorio en GitHub](https://github.com/opencv/opencv)

## Instalación

### Instalación en Windows

#### Método 1: Descargar OpenCV preconfigurado desde GitHub (Python y C++) (Recomendado)

1. Descarga la ultima [version](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/) desde la pagina de Sourceforge.
2. Descomprime en `C:\opencv`.
3. Edita las variables de entorno (busca "Variables de entorno").
4. Agrega `C:\opencv\bin` al `Path`.
5. Reinicia la computadora.
6. Verifica la variable de entorno con `echo %Path%`.

#### Método 2: Usar pip para instalar la versión preconfigurada de OpenCV para Python

1. Abre la terminal (Ctrl+R + cmd).
2. Verifica la instalación de Python3: `py --version`.
3. Ve a [PyPi OpenCV](https://pypi.org/project/opencv-python/) para más detalles.
4. Ejecuta el siguiente comando:  
   ```bash
   py -m pip install opencv-contrib-python
   ```
5. Verifica la instalación en Python REPL:  
   ```python
   import cv2
   ```

#### Método 3: Construir OpenCV desde fuentes (Python y C++)

1. Instala [CMake](https://cmake.org/download/) y verifica con `cmake --version`.
2. Descarga los códigos fuente desde los [releases de OpenCV](https://github.com/opencv/opencv/releases/tag/4.5.1) y [opencv_contrib](https://github.com/opencv/opencv_contrib/releases/tag/4.5.1).
3. Descomprime ambos archivos.
4. Abre `cmake-gui`, selecciona el directorio de OpenCV, y configura el proyecto.
5. Construye usando Visual Studio (`BUILD_ALL` y `INSTALL`).
6. Edita las variables de entorno para incluir `C:\opencv-custom\bin`.
7. Reinicia la computadora y verifica con `echo %Path%`.

### Instalación en Linux

En Linux, la instalación de OpenCV generalmente se realiza compilando desde el código fuente o utilizando el gestor de paquetes del sistema.

1. Instala dependencias:
   ```bash
   sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
   ```
2. Clona el repositorio de OpenCV y opencv_contrib:
   ```bash
   git clone https://github.com/opencv/opencv.git
   git clone https://github.com/opencv/opencv_contrib.git
   ```
3. Crea una carpeta de compilación y configura CMake:
   ```bash
   cd opencv
   mkdir build
   cd build
   cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
   ```
4. Compila OpenCV:
   ```bash
   make -j$(nproc)
   sudo make install
   ```

## Contenido del repositorio

### Presentaciones

- **NerdTalk - OpenCV**: Resumen de una presentación interna sobre el uso de OpenCV en la empresa.

### Ejemplos

1. **TestOpenCV-Windows**: Ejemplo desarrollado en Qt Creator bajo Windows, que captura la cámara y aplica varios filtros (bordes).
2. **QTOpenCV-Linux**: Similar al ejemplo anterior, pero en Linux.
3. **Prueba_OpenCV_Docker**: Un ejemplo básico que se ejecuta dentro de Docker. Lee una imagen y aplica un filtro de detección de bordes.
4. **opencv1, opencv2, opencv3**: Ejemplos básicos en C++ para el uso de OpenCV.
5. **opencvharry**: Ejemplo divertido en Python que simula un efecto de "capa de invisibilidad", similar al de Harry Potter, mostrando una imagen previa.

## Uso

Para ejecutar los ejemplos en Windows, Linux o Docker, sigue las instrucciones incluidas en cada uno de los directorios.

---
