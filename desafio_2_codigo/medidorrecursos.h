#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

class MedidorRecurso {
private:
    long long iteracionesActuales;
    unsigned long long memoriaHeapBytes;
    unsigned long long memoriaStackBytes;

public:
    // Constructores y Destructor explícitos
    MedidorRecurso();
    MedidorRecurso(long long iteraciones, unsigned long long heap, unsigned long long stack);
    MedidorRecurso(const MedidorRecurso& otra);
    MedidorRecurso& operator=(const MedidorRecurso& otra);
    ~MedidorRecurso();

    // Métodos inline para bucles críticos
    inline void registrarIteracion(int cantidad = 1) {
        iteracionesActuales += cantidad;
    }

    inline void reiniciarIteraciones() {
        iteracionesActuales = 0;
    }

    // Setters explícitos
    void setIteraciones(long long iteraciones);
    void setMemoriaHeap(unsigned long long bytes);
    void setMemoriaStack(unsigned long long bytes);

    // Getters explícitos
    long long getIteraciones() const;
    unsigned long long getMemoriaHeap() const;
    unsigned long long getMemoriaStack() const;

    // Auditoría de Heap
    void registrarMemoriaHeap(unsigned long long bytes);
    void liberarMemoriaHeap(unsigned long long bytes);

    // Reporte por consola
    void reportarRecursos() const;
};

#endif // MEDIDORRECURSOS_H