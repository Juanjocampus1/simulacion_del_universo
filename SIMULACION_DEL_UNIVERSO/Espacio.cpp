#include "Espacio.h"

void Espacio::agregarNodo(float x, float y, float z) {
    nodos.emplace_back(x, y, z);
}

void Espacio::agregarConexion(int nodo1, int nodo2) {
    conexiones.emplace_back(nodo1, nodo2);
}
