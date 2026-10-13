#include "RedAmigos.h"

void RedAmigos::liberarMemoria() {
    if (matrizConexiones != nullptr) {
        delete[] matrizConexiones; // Liberación garantizada en 1 solo paso O(1)
        matrizConexiones = nullptr;
    }
    totalUsuarios = 0;
}

// Constructor: Reserva 1 solo bloque continuo inicializado en false
RedAmigos::RedAmigos(int totalUsuarios) {
    this->totalUsuarios = (totalUsuarios > 0) ? totalUsuarios : 0;
    if (this->totalUsuarios > 0) {
        // En C++, new bool[size]() con paréntesis vacíos inicializa a false automáticamente
        matrizConexiones = new bool[this->totalUsuarios * this->totalUsuarios]();
    } else {
        matrizConexiones = nullptr;
    }
}

// Destructor
RedAmigos::~RedAmigos() {
    liberarMemoria();
}

// Constructor de Copia (Copia rápida contigua)
RedAmigos::RedAmigos(const RedAmigos& otra) {
    totalUsuarios = otra.totalUsuarios;
    if (totalUsuarios > 0) {
        int limite = totalUsuarios * totalUsuarios;
        matrizConexiones = new bool[limite];
        for (int i = 0; i < limite; ++i) {
            matrizConexiones[i] = otra.matrizConexiones[i];
        }
    } else {
        matrizConexiones = nullptr;
    }
}

// Operador de Asignación (Protección contra autoasignación y copia limpia)
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

// Acceso $O(1)$ simétrico en bloque único
void RedAmigos::registrarAmistad(int idUsuario1, int idUsuario2) {
    if (idUsuario1 >= 0 && idUsuario1 < totalUsuarios &&
        idUsuario2 >= 0 && idUsuario2 < totalUsuarios &&
        idUsuario1 != idUsuario2) {

        matrizConexiones[idUsuario1 * totalUsuarios + idUsuario2] = true;
        matrizConexiones[idUsuario2 * totalUsuarios + idUsuario1] = true;
    }
}

// Consulta $O(1)$ con cálculo de desfase directo
bool RedAmigos::sonAmigos(int idUsuario1, int idUsuario2) const {
    if (idUsuario1 >= 0 && idUsuario1 < totalUsuarios &&
        idUsuario2 >= 0 && idUsuario2 < totalUsuarios) {
        return matrizConexiones[idUsuario1 * totalUsuarios + idUsuario2];
    }
    return false;
}

// Recorrido lineal continuo optimizado para la Caché de la CPU
int RedAmigos::contarAmigosEnComun(int idUsuario1, int idUsuario2) const {
    if (idUsuario1 < 0 || idUsuario1 >= totalUsuarios ||
        idUsuario2 < 0 || idUsuario2 >= totalUsuarios ||
        idUsuario1 == idUsuario2) {
        return 0;
    }

    // Calculamos los desplazamientos base fuera del ciclo para ahorrar iteraciones
    int base1 = idUsuario1 * totalUsuarios;
    int base2 = idUsuario2 * totalUsuarios;
    int comunes = 0;

    for (int i = 0; i < totalUsuarios; ++i) {
        // Al estar contiguos en memoria, la lectura es secuencial a máxima velocidad
        if (matrizConexiones[base1 + i] && matrizConexiones[base2 + i]) {
            comunes++;
        }
    }
    return comunes;
}

int RedAmigos::obtenerTotalUsuarios() const {
    return totalUsuarios;
}