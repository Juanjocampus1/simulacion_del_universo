#pragma once

#include <vector>

using namespace std;

class Tensor {
private:
    int dimension;
    vector<vector<float>> matriz;

public:
    Tensor(int dim);
    void asignarValor(int fila, int columna, float valor);
    float obtenerValor(int fila, int columna) const;
};
