#ifndef REDAMIGOS_H
#define REDAMIGOS_H

class RedAmigos {
private:
    bool* matrizConexiones;
    int totalUsuarios;

    void liberarMemoria();

public:
    RedAmigos();
    RedAmigos(int totalUsuarios);
    RedAmigos(const RedAmigos& otra);
    RedAmigos& operator=(const RedAmigos& otra);
    ~RedAmigos();

    int getTotalUsuarios() const;

    void registrarAmistad(int idUsuario1, int idUsuario2);
    void redimensionar(int nuevoTotal);
    bool sonAmigos(int idUsuario1, int idUsuario2) const;
    int contarAmigosEnComun(int idUsuario1, int idUsuario2) const;
};

#endif // REDAMIGOS_H