#include "medidorrecursos.h"
#include <iostream>

using namespace std;

MedidorRecurso::MedidorRecurso()
    : iteracionesActuales(0), memoriaHeapBytes(0), memoriaStackBytes(0) {
}

MedidorRecurso::MedidorRecurso(long long iteraciones, unsigned long long heap, unsigned long long stack)
    : iteracionesActuales(iteraciones), memoriaHeapBytes(heap), memoriaStackBytes(stack) {
}

MedidorRecurso::MedidorRecurso(const MedidorRecurso& otra)
    : iteracionesActuales(otra.iteracionesActuales),
    memoriaHeapBytes(otra.memoriaHeapBytes),
    memoriaStackBytes(otra.memoriaStackBytes) {
}

MedidorRecurso& MedidorRecurso::operator=(const MedidorRecurso& otra) {
    if (this != &otra) {
        iteracionesActuales = otra.iteracionesActuales;
        memoriaHeapBytes = otra.memoriaHeapBytes;
        memoriaStackBytes = otra.memoriaStackBytes;
    }
    return *this;
}

MedidorRecurso::~MedidorRecurso() {
}

// Setters explícitos
void MedidorRecurso::setIteraciones(long long iteraciones) {
    iteracionesActuales = iteraciones;
}

void MedidorRecurso::setMemoriaHeap(unsigned long long bytes) {
    memoriaHeapBytes = bytes;
}

void MedidorRecurso::setMemoriaStack(unsigned long long bytes) {
    memoriaStackBytes = bytes;
}

// Getters explícitos
long long MedidorRecurso::getIteraciones() const {
    return iteracionesActuales;
}

unsigned long long MedidorRecurso::getMemoriaHeap() const {
    return memoriaHeapBytes;
}

unsigned long long MedidorRecurso::getMemoriaStack() const {
    return memoriaStackBytes;
}

// Auditoría
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

void MedidorRecurso::reportarRecursos() const {
    cout << "\n============================================\n";
    cout << "        REPORTE DE METRICAS Y RECURSOS      \n";
    cout << "============================================\n";
    cout << " -> Iteraciones acumuladas : " << iteracionesActuales << "\n";
    cout << " -> Memoria Heap en uso    : " << memoriaHeapBytes << " bytes\n";
    cout << " -> Memoria Stack estimada : " << memoriaStackBytes << " bytes\n";
    cout << "============================================\n\n";
}