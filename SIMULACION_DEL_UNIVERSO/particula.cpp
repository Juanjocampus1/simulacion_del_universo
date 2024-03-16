#define _USE_MATH_DEFINES

#include "Particula.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

Particula::Particula(float m, float x, float y, float z, float tam, float r, float g, float b)
    : masa(m), posX(x), posY(y), posZ(z), tamano(tam) {
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Particula::dibujar() {
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glColor3f(color[0], color[1], color[2]);
    dibujarEsfera(tamano, 20, 20);
    glPopMatrix();
}

void Particula::dibujarEsfera(float radio, int segmentos, int anillos) {
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