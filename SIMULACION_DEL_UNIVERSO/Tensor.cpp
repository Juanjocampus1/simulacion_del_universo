#include "Tensor.h"

using namespace std;

Tensor::Tensor(int dim) : dimension(dim), matriz(dim, vector<float>(dim, 0.0f)) {}

void Tensor::asignarValor(int fila, int columna, float valor) {
    matriz[fila][columna] = valor;
}

float Tensor::obtenerValor(int fila, int columna) const {
    return matriz[fila][columna];
}
