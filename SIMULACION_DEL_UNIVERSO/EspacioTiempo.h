#pragma once

#include "Particula.h"

class EspacioTiempo {
private:
    static const int ancho = 100;
    static const int alto = 100;
    static const int profundidad = 100;
    float paso_tiempo = 0.1f;

    struct PuntoEspacioTiempo {
        float densidad;
        Particula particula;
    };

    PuntoEspacioTiempo*** espacio_tiempo;

public:
    EspacioTiempo();
    ~EspacioTiempo();

    float obtenerDensidad(int x, int y, int z);

    int obtenerAncho() const { return ancho; }
    int obtenerAlto() const { return alto; }
    int obtenerProfundidad() const { return profundidad; }
    PuntoEspacioTiempo*** obtenerEspacioTiempo() const { return espacio_tiempo; }

    void introducirParticula(const Particula& particula);
    void evolucionarEspacioTiempo();
    void dibujarParticulas();
};
