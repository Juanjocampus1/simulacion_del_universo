#pragma once

#include <vector>
#include "Nodo.h"

using namespace std;

class Espacio {
private:
    vector<Nodo> nodos;
    vector<Conexion> conexiones;

public:
    Espacio() = default;

    void agregarNodo(float x, float y, float z);
    void agregarConexion(int nodo1, int nodo2);

    const vector<Nodo>& obtenerNodos() const { return nodos; }
    const vector<Conexion>& obtenerConexiones() const { return conexiones; }

};
