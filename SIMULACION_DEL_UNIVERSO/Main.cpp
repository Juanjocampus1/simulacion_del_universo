#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>
#include <iomanip>
#include "FPSCounter.h"
#include "EspacioTiempo.h"
#include "PuntoEspacioTiempo.h"

using namespace std;

int main() {

    if (!glfwInit()) {
        fprintf(stderr, "Error al inicializar GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Simulacion del Universo", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Error al crear la ventana de GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Error al inicializar GLEW\n");
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

    EspacioTiempo espacioTiempo;

    Particula nuevaParticula(1.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f, 0.0f, 0.0f);
    
    if (nuevaParticula.masa > 0.0f) {
        espacioTiempo.introducirParticula(nuevaParticula);
        fprintf(stderr, "la particula se ha generado correctamente");
    }
    else {
        fprintf(stderr, "la particula a generar no tiene masa");
    }

    FPSCounter fpsCounter;

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        espacioTiempo.evolucionarEspacioTiempo();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int ancho = espacioTiempo.obtenerAncho();
        int alto = espacioTiempo.obtenerAlto();
        int profundidad = espacioTiempo.obtenerProfundidad();
        PuntoEspacioTiempo*** espacio_tiempo = espacioTiempo.obtenerEspacioTiempo();

        for (int i = 0; i < ancho; ++i) {
            for (int j = 0; j < alto; ++j) {
                for (int k = 0; k < profundidad; ++k) {
                    if (espacio_tiempo[i][j][k].densidad > 0.0f) {
                        espacio_tiempo[i][j][k].particula.dibujar();
                    }
                }
            }
        }

        fpsCounter.frameRendered();

        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}



/*
#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

class Particula {
public:
    float masa;
    float posX;
    float posY;
    float posZ;

    Particula(float m, float x, float y, float z)
        : masa(m), posX(x), posY(y), posZ(z) {}
};

class PuntoEspacioTiempo {
public:
    float densidad;

    PuntoEspacioTiempo() : densidad(0.0f) {}
};

class EspacioTiempo {
private:
    static const int ancho = 100;
    static const int alto = 100;
    static const int profundidad = 100;
    float paso_tiempo = 0.1f;

    PuntoEspacioTiempo*** espacio_tiempo;

public:
    EspacioTiempo() {
        espacio_tiempo = new PuntoEspacioTiempo * *[ancho];
        for (int i = 0; i < ancho; ++i) {
            espacio_tiempo[i] = new PuntoEspacioTiempo * [alto];
            for (int j = 0; j < alto; ++j) {
                espacio_tiempo[i][j] = new PuntoEspacioTiempo[profundidad];
                for (int k = 0; k < profundidad; ++k) {
                    espacio_tiempo[i][j][k].densidad = 0.0f;
                }
            }
        }
    }

    ~EspacioTiempo() {
        for (int i = 0; i < ancho; ++i) {
            for (int j = 0; j < alto; ++j) {
                delete[] espacio_tiempo[i][j];
            }
            delete[] espacio_tiempo[i];
        }
        delete[] espacio_tiempo;
    }

    void introducirParticula(const Particula& particula) {
        int x = static_cast<int>(particula.posX * ancho);
        int y = static_cast<int>(particula.posY * alto);
        int z = static_cast<int>(particula.posZ * profundidad);

        espacio_tiempo[x][y][z].densidad += particula.masa;
    }

    void dibujarParticulas() {
        for (int i = 0; i < ancho; ++i) {
            for (int j = 0; j < alto; ++j) {
                for (int k = 0; k < profundidad; ++k) {
                    if (espacio_tiempo[i][j][k].densidad > 0.0f) {
                        dibujarParticula(i, j, k);
                    }
                }
            }
        }
    }

    void evolucionarEspacioTiempo() {
        for (int i = 0; i < ancho; ++i) {
            for (int j = 0; j < alto; ++j) {
                for (int k = 0; k < profundidad; ++k) {
                    espacio_tiempo[i][j][k].densidad += paso_tiempo;
                }
            }
        }
    }

private:
    void dibujarParticula(float x, float y, float z) {
        glPushMatrix();
        glTranslatef(x, y, z);
        dibujarEsfera(0.05, 10, 10);
        glPopMatrix();
    }

    void dibujarEsfera(float radio, int segmentos, int anillos) {
        for (int i = 0; i <= anillos; ++i) {
            double lat0 = M_PI * (-0.5 + (i - 1) / static_cast<double>(anillos));
            double z0 = sin(lat0);
            double zr0 = cos(lat0);

            double lat1 = M_PI * (-0.5 + i / static_cast<double>(anillos));
            double z1 = sin(lat1);
            double zr1 = cos(lat1);

            glBegin(GL_QUAD_STRIP);
            for (int j = 0; j <= segmentos; ++j) {
                double lng = 2 * M_PI * (j - 1) / static_cast<double>(segmentos);
                double x = cos(lng);
                double y = sin(lng);

                glNormal3f(x * zr0, y * zr0, z0);
                glVertex3f(x * zr0, y * zr0, z0);

                glNormal3f(x * zr1, y * zr1, z1);
                glVertex3f(x * zr1, y * zr1, z1);
            }
            glEnd();
        }
    }
};

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Error al inicializar GLFW\n");
        return -1;
    }

    // Configurar GLFW para utilizar OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear una ventana
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Simulacion del Universo", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Error al crear la ventana de GLFW\n");
        glfwTerminate();
        return -1;
    }

    // Configurar el contexto de OpenGL
    glfwMakeContextCurrent(window);

    // Inicializar GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Error al inicializar GLEW\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    glViewport(0, 0, 1920, 1080);

    EspacioTiempo espacioTiempo;

    while (!glfwWindowShouldClose(window)) {
        // Procesar eventos (entrada del usuario, etc.)
        glfwPollEvents();

        // Evolucionar el espacio-tiempo en función del tiempo
        espacioTiempo.evolucionarEspacioTiempo();

        // Limpiar el búfer de color y profundidad antes de renderizar
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibujar partículas en el espacio
        espacioTiempo.dibujarParticulas();

        // Intercambiar buffers y actualizar la ventana
        glfwSwapBuffers(window);
    }

    // Limpiar y cerrar GLFW al finalizar
    glfwTerminate();
    return 0;
}
*/