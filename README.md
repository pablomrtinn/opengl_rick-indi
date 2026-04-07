# Actividad 2: Rick

Este es un proyecto de gráficos por computador desarrollado con **C++**, **OpenGL 3.3** y el framework **Qt**. El proyecto consiste en una escena 3D interactiva que presenta al personaje Rick, una videocámara y una puerta automática con lógica de colisión/proximidad.

<img width="338" height="307" alt="image" src="https://github.com/user-attachments/assets/62f58136-bab6-4f5b-8c27-e83c3debc8fd" />

---

## 🛠️ Tecnologías Utilizadas
* **Lenguaje:** C++
* **Gráficos:** OpenGL 3.3 (Core Profile)
* **Framework UI:** Qt (QOpenGLWidget)
* **Librería Matemática:** GLM (OpenGL Mathematics)

---

## 🚀 Funcionalidades Principales

### 1. Sistema de Cámaras
El proyecto implementa dos modos de visualización:
* **Cámara Libre:** Una cámara en perspectiva que permite orbitar alrededor de la escena usando el ratón.
* **Videocámara (Modo FPS/Fijo):** Una cámara situada en una posición específica (`obs`) que sigue siempre al personaje Rick (`vrp = posRick`).

### 2. Control de Personaje (Rick)
* **Movimiento Manual:** Mediante las teclas de dirección, Rick puede desplazarse por el escenario.
* **Modo Automático:** Un temporizador (`QTimer`) gestiona el movimiento autónomo de Rick de un lado a otro de la escena.

### 3. Elementos Interactivos
* **Puerta Automática:** Se ha implementado un "cubo rojo" que actúa como puerta. Esta se abre (desliza) automáticamente cuando Rick se acerca a los extremos de la sala y se cierra cuando está en la zona central.
* **Modelos 3D:** Carga dinámica de archivos `.obj` para Rick y la Videocámara.

---

## 🎮 Controles de Teclado
| Tecla | Acción |
| :--- | :--- |
| **Flecha Arriba** | Mueve a Rick hacia la derecha ($+X$). |
| **Flecha Abajo** | Mueve a Rick hacia la izquierda ($-X$). |
| **C** | Alterna entre la cámara libre y la videocámara. |
| **A** | Activa/Desactiva el modo de movimiento automático. |
| **R** | Reinicia la escena y la cámara a su estado inicial. |

---

## 🖱️ Controles de Ratón
* **Click Izquierdo + Arrastrar:** Rota la cámara en el modo de cámara libre.

---

## 🏗️ Estructura del Código
* `MyGLWidget`: Extiende la funcionalidad base para añadir la lógica específica de la cámara, el movimiento de Rick y la animación de la puerta.
* `BL2GLWidget`: Clase base que gestiona la configuración inicial de OpenGL, carga de modelos, creación de buffers (VAOs/VBOs) y shaders básicos.
* `main.cpp`: Punto de entrada que configura el formato de superficie de OpenGL 3.3 Core Profile.
* `MyForm`: Clase para la interfaz de usuario de Qt que integra el widget de OpenGL.

---

## 🛠️ Instalación y Compilación
1. Asegúrate de tener instalado **Qt Creator** y las librerías de **OpenGL**.
2. Abre el archivo de proyecto (`.pro`) en Qt Creator.
3. Asegúrate de que los modelos (`.obj`) estén en la carpeta `./models/` y los shaders en `./shaders/`.
4. Compila y ejecuta.
