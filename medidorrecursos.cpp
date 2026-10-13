#include "medidorrecursos.h"
#include <iostream>

using namespace std;

MedidorRecurso::MedidorRecurso()
    : iteracionesActuales(0), memoriaHeapBytes(0), memoriaStackBytes(0) {
}

MedidorRecurso::~MedidorRecurso() {
}

void MedidorRecurso::registrarMemoriaHeap(unsigned long long bytes) {
    memoriaHeapBytes += bytes;
}

void MedidorRecurso::liberarMemoriaHeap(unsigned long long bytes) {
    if (bytes <= memoriaHeapBytes) {
        memoriaHeapBytes -= bytes;
    } else {
        memoriaHeapBytes = 0;
    }
}

void MedidorRecurso::reiniciarMemoriaHeap() {
    memoriaHeapBytes = 0;
}

void MedidorRecurso::registrarMemoriaStack(unsigned long long bytes) {
    memoriaStackBytes = bytes;
}

long long MedidorRecurso::obtenerIteraciones() const {
    return iteracionesActuales;
}

unsigned long long MedidorRecurso::obtenerMemoriaHeap() const {
    return memoriaHeapBytes;
}

unsigned long long MedidorRecurso::obtenerMemoriaStack() const {
    return memoriaStackBytes;
}

void MedidorRecurso::reportarRecursos() const {

    cout << " -> Iteraciones acumuladas : " << iteracionesActuales << "\n";
    cout << " -> Memoria Heap en uso    : " << memoriaHeapBytes << " bytes\n";
    cout << " -> Memoria Stack estimada : " << memoriaStackBytes << " bytes\n";
}