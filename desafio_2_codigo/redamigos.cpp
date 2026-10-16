#include "redamigos.h"



void RedAmigos::liberarMemoria() {
    if (matrizConexiones != nullptr) {
        delete[] matrizConexiones;
        matrizConexiones = nullptr;
    }
    totalUsuarios = 0;
}

RedAmigos::RedAmigos()
    : matrizConexiones(nullptr), totalUsuarios(0) {
}

RedAmigos::RedAmigos(int totalUsuarios)
    : matrizConexiones(nullptr), totalUsuarios(totalUsuarios > 0 ? totalUsuarios : 0) {

        if (this->totalUsuarios > 0) {
            int total = this->totalUsuarios * this->totalUsuarios;
            matrizConexiones = new bool[total]();
        }
    }


RedAmigos::RedAmigos(const RedAmigos& otra)
    : matrizConexiones(nullptr), totalUsuarios(otra.totalUsuarios) {
    if (totalUsuarios > 0) {
        int limite = totalUsuarios * totalUsuarios;
        matrizConexiones = new bool[limite];
        for (int i = 0; i < limite; ++i) {
            matrizConexiones[i] = otra.matrizConexiones[i];
        }
    }
}

RedAmigos& RedAmigos::operator=(const RedAmigos& otra) {
    if (this != &otra) {
        liberarMemoria();
        totalUsuarios = otra.totalUsuarios;
        if (totalUsuarios > 0) {
            int limite = totalUsuarios * totalUsuarios;
            matrizConexiones = new bool[limite];
            for (int i = 0; i < limite; ++i) {
                matrizConexiones[i] = otra.matrizConexiones[i];
            }
        }
    }
    return *this;
}

RedAmigos::~RedAmigos() {
    liberarMemoria();
}

int RedAmigos::getTotalUsuarios() const {
    return totalUsuarios;
}

void RedAmigos::registrarAmistad(int idUsuario1, int idUsuario2) {
    if (idUsuario1 >= 0 && idUsuario1 < totalUsuarios &&
        idUsuario2 >= 0 && idUsuario2 < totalUsuarios &&
        idUsuario1 != idUsuario2) {

        matrizConexiones[idUsuario1 * totalUsuarios + idUsuario2] = true;
        matrizConexiones[idUsuario2 * totalUsuarios + idUsuario1] = true;
    }
}

bool RedAmigos::sonAmigos(int idUsuario1, int idUsuario2) const {
    if (idUsuario1 >= 0 && idUsuario1 < totalUsuarios &&
        idUsuario2 >= 0 && idUsuario2 < totalUsuarios) {
        return matrizConexiones[idUsuario1 * totalUsuarios + idUsuario2];
    }
    return false;
}

int RedAmigos::contarAmigosEnComun(int idUsuario1, int idUsuario2) const {
    if (idUsuario1 < 0 || idUsuario1 >= totalUsuarios ||
        idUsuario2 < 0 || idUsuario2 >= totalUsuarios ||
        idUsuario1 == idUsuario2) {
        return 0;
    }

    int base1 = idUsuario1 * totalUsuarios;
    int base2 = idUsuario2 * totalUsuarios;
    int comunes = 0;

    for (int i = 0; i < totalUsuarios; ++i) {
        if (matrizConexiones[base1 + i] && matrizConexiones[base2 + i]) {
            comunes++;
        }
    }
    return comunes;
}

void RedAmigos::redimensionar(int nuevoTotal) {
    if (nuevoTotal <= totalUsuarios) return;
    bool* nuevaMatriz = new bool[nuevoTotal * nuevoTotal]();
    if (matrizConexiones != nullptr) {
        for (int i = 0; i < totalUsuarios; ++i) {
            for (int j = 0; j < totalUsuarios; ++j) {
                nuevaMatriz[i * nuevoTotal + j] = matrizConexiones[i * totalUsuarios + j];
            }
        }
        delete[] matrizConexiones;
    }
    matrizConexiones = nuevaMatriz;
    totalUsuarios = nuevoTotal;
}