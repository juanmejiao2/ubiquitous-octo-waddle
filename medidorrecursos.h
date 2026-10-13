#ifndef MEDIDOR_RECURSO_H
#define MEDIDOR_RECURSO_H


class MedidorRecurso {
private:
    long long iteracionesActuales;
    unsigned long long memoriaHeapBytes;
    unsigned long long memoriaStackBytes;

public:
    MedidorRecurso();
    ~MedidorRecurso();

    inline void registrarIteracion(int cantidad = 1) {
        iteracionesActuales += cantidad;
    }

    inline void reiniciarIteraciones() {
        iteracionesActuales = 0;
    }

    void registrarMemoriaHeap(unsigned long long bytes);
    void liberarMemoriaHeap(unsigned long long bytes);
    void reiniciarMemoriaHeap();

    void registrarMemoriaStack(unsigned long long bytes);

    long long obtenerIteraciones() const;
    unsigned long long obtenerMemoriaHeap() const;
    unsigned long long obtenerMemoriaStack() const;

    void reportarRecursos() const;
};

#endif // MEDIDOR_RECURSO_H