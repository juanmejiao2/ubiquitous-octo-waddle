#ifndef SISTEMAUDEABOOK_H
#define SISTEMAUDEABOOK_H

#include "usuario.h"
#include "redamigos.h"
#include "medidorrecursos.h"
#include "arreglodinamico.h"
#include "cadena.h"
#include<fstream>


class SistemaUdeaBook {
private:
    ArregloDinamico<Usuario> usuarios;
    RedAmigos matrizAmistades;
    MedidorRecurso medidor;
    int usuarioAutenticadoIndex;
    bool yaAlternoFotos;

    Cadena leerCadenaDesdeArchivo(std::ifstream& archivo, char delimitador);

public:
    SistemaUdeaBook();
    SistemaUdeaBook(const SistemaUdeaBook& otro);
    SistemaUdeaBook& operator=(const SistemaUdeaBook& otro);
    ~SistemaUdeaBook();

    void cargarDatos();
    void guardarDatos();
    void ejecutarMenu();
    bool iniciarSesion(Cadena correo, Cadena contrasena);
    bool registrarUsuario(const Usuario& nuevoUsuario);
    void mostrarMejoresAmigos();
    void cambiarFotosPerfil();
    void enviarSolicitudAmistad(Cadena receptor);
    void aceptarSolicitudAmistad(Cadena emisor);
    void verSugerenciasAmistad(int idUsuario);
    void visitarPerfilAmigo(Cadena nombreAmigo);
    void enviarMensaje(Cadena receptor, Cadena contenido);
    void leerNuevosMensajes();
    void buscarMensajesPorFecha(Cadena fecha, Cadena emisor);

    ArregloDinamico<Usuario>& getUsuarios();
    RedAmigos& getMatrizAmistades();
    MedidorRecurso& getMedidor();
    int getUsuarioAutenticadoIndex() const;
    bool getYaAlternoFotos() const;

    void setUsuarioAutenticadoIndex(int index);
    void setYaAlternoFotos(bool alterno);
};

#endif // SISTEMAUDEABOOK_H