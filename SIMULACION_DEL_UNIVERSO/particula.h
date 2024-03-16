#pragma once

class Particula {
public:
    float masa;
    float posX;
    float posY;
    float posZ;
    float tamano;
    float color[3]; 


    Particula(float m, float x, float y, float z, float tam, float r, float g, float b);

    void dibujar();
    static void dibujarEsfera(float radio, int segmentos, int anillos);
};
