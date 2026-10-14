#include "medidorrecursos.h"
#include <iostream>

using namespace std;

MedidorRecurso::MedidorRecurso()
    : iteracionesActuales(0), memoriaHeapBytes(0), memoriaStackBytes(0) {
}

MedidorRecurso::MedidorRecurso(long long iteraciones, size_t heap, size_t stack)
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

long long MedidorRecurso::getIteraciones() const {
    return iteracionesActuales;
}

size_t MedidorRecurso::getMemoriaHeap() const {
    return memoriaHeapBytes;
}

size_t MedidorRecurso::getMemoriaStack() const {
    return memoriaStackBytes;
}

void MedidorRecurso::setIteraciones(long long iteraciones) {
    iteracionesActuales = iteraciones;
}

void MedidorRecurso::setMemoriaHeap(size_t bytes) {
    memoriaHeapBytes = bytes;
}

void MedidorRecurso::setMemoriaStack(size_t bytes) {
    memoriaStackBytes = bytes;
}

void MedidorRecurso::registrarMemoriaHeap(size_t bytes) {
    memoriaHeapBytes += bytes;
}

void MedidorRecurso::reportarRecursos() const {
    cout << " -> Iteraciones acumuladas : " << iteracionesActuales << "\n";
    cout << " -> Memoria Heap en uso    : " << memoriaHeapBytes << " bytes\n";
    cout << " -> Memoria Stack estimada : " << memoriaStackBytes << " bytes\n";
}