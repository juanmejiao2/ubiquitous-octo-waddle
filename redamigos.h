#ifndef REDAMIGOS_H
#define REDAMIGOS_H

class RedAmigos {
private:
    bool* matrizConexiones; // Matriz aplanada 1D en Heap
    int totalUsuarios;

    void liberarMemoria();

public:
    // Constructores y Destructor explícitos
    RedAmigos();
    RedAmigos(int totalUsuarios);
    RedAmigos(const RedAmigos& otra);
    RedAmigos& operator=(const RedAmigos& otra);
    ~RedAmigos();

    // Getter explícito
    int getTotalUsuarios() const;

    // Métodos de Dominio
    void registrarAmistad(int idUsuario1, int idUsuario2);
    bool sonAmigos(int idUsuario1, int idUsuario2) const;
    int contarAmigosEnComun(int idUsuario1, int idUsuario2) const;
};

#endif // REDAMIGOS_H