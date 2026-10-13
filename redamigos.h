#ifndef RED_AMIGOS_H
#define RED_AMIGOS_H

class RedAmigos {
private:
    bool* matrizConexiones;
    int totalUsuarios;

    void liberarMemoria();

public:
    explicit RedAmigos(int totalUsuarios = 0);
    ~RedAmigos();

    RedAmigos(const RedAmigos& otra);
    RedAmigos& operator=(const RedAmigos& otra);

    void registrarAmistad(int idUsuario1, int idUsuario2);
    bool sonAmigos(int idUsuario1, int idUsuario2) const;
    int contarAmigosEnComun(int idUsuario1, int idUsuario2) const;
    int obtenerTotalUsuarios() const;
};

#endif // RED_AMIGOS_H