#define _USE_MATH_DEFINES

#include <PuntoEspacioTiempo.h>
#include "EspacioTiempo.h"
#include <GL/glew.h>
#include <cmath>
#include <thread>
#include <vector>

EspacioTiempo::EspacioTiempo() {
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

EspacioTiempo::~EspacioTiempo() {
    for (int i = 0; i < ancho; ++i) {
        for (int j = 0; j < alto; ++j) {
            delete[] espacio_tiempo[i][j];
        }
        delete[] espacio_tiempo[i];
    }
    delete[] espacio_tiempo;
}

void EspacioTiempo::introducirParticula(const Particula& particula) {
    int x = static_cast<int>(particula.posX * ancho);
    int y = static_cast<int>(particula.posY * alto);
    int z = static_cast<int>(particula.posZ * profundidad);

    espacio_tiempo[x][y][z].densidad += particula.masa;
    espacio_tiempo[x][y][z].particula = particula;
}

void EspacioTiempo::evolucionarEspacioTiempo() {
    for (int i = 0; i < ancho; ++i) {
        for (int j = 0; j < alto; ++j) {
            for (int k = 0; k < profundidad; ++k) {
                espacio_tiempo[i][j][k].densidad += paso_tiempo;
            }
        }
    }
}

float EspacioTiempo::obtenerDensidad(int x, int y, int z) {
    return espacio_tiempo[x][y][z].densidad;
}

void EspacioTiempo::dibujarParticulas() {
    for (int i = 0; i < ancho; ++i) {
        for (int j = 0; j < alto; ++j) {
            for (int k = 0; k < profundidad; ++k) {
                if (espacio_tiempo[i][j][k].particula.masa > 0.0f) {
                    espacio_tiempo[i][j][k].particula.dibujar();
                }
            }
        }
    }
}
