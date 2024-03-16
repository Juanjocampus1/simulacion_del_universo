#pragma once

#include <vector>

class Nodo {
public:
    float posX;
    float posY;
    float posZ;

    Nodo(float x, float y, float z) : posX(x), posY(y), posZ(z) {}
};

class Conexion {
public:
    int nodo1;
    int nodo2;

    Conexion(int n1, int n2) : nodo1(n1), nodo2(n2) {}
};

class Espacio {
private:
    std::vector<Nodo> nodos;
    std::vector<Conexion> conexiones;

public:
    void agregarNodo(float x, float y, float z);
    void agregarConexion(int nodo1, int nodo2);

    const std::vector<Nodo>& obtenerNodos() const { return nodos; }
    const std::vector<Conexion>& obtenerConexiones() const { return conexiones; }
};
