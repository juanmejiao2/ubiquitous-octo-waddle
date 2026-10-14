#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <cstddef>

class MedidorRecurso {
private:
    long long iteracionesActuales;
    size_t memoriaHeapBytes;
    size_t memoriaStackBytes;

public:
    MedidorRecurso();
    MedidorRecurso(long long iteraciones, size_t heap, size_t stack);
    MedidorRecurso(const MedidorRecurso& otra);
    MedidorRecurso& operator=(const MedidorRecurso& otra);
    ~MedidorRecurso();

    inline void registrarIteracion(int cantidad = 1) {
        iteracionesActuales += cantidad;
    }

    inline void reiniciarIteraciones() {
        iteracionesActuales = 0;
    }

    void registrarMemoriaHeap(size_t bytes);
    void reportarRecursos() const;

    long long getIteraciones() const;
    size_t getMemoriaHeap() const;
    size_t getMemoriaStack() const;

    void setIteraciones(long long iteraciones);
    void setMemoriaHeap(size_t bytes);
    void setMemoriaStack(size_t bytes);
};

#endif // MEDIDORRECURSOS_H