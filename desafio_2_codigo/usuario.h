#ifndef USUARIO_H
#define USUARIO_H

#include "cadena.h"
#include "arreglodinamico.h"
#include "mensaje.h"
#include "solicitudamistad.h"
#include "album.h"

class Usuario{
private:
    Cadena NombreUsuario;
    Cadena FechaNacimiento;
    Cadena Correo;
    Cadena FotoPerfil;
    Cadena Contrasena;
    Cadena Ciudad;
    Cadena Pais;
    Cadena FechaInscripcion;
    ArregloDinamico<int> idsAmigos;
    ArregloDinamico<Mensaje> mensajesEnviados;
    ArregloDinamico<Mensaje> mensajesRecibidos;
    ArregloDinamico<SolicitudAmistad> solicitudes;
    ArregloDinamico<Album> albumes;

public:
    Usuario();
    Usuario(Cadena nombreusuario, Cadena fechanacimiento, Cadena correo, Cadena fotoperfil, Cadena contrasena, Cadena ciudad, Cadena pais, Cadena fechainscripcion);
    Cadena GETNombreUsuario() const;
    bool validarContrasenia(Cadena pass) const;
    void agregarAmigo(int idAmigo);
    void agregarAlbum(const Album& album);
    void recibirMensaje(const Mensaje& mensaje);
    void recibirSolicitud(const SolicitudAmistad& solicitud);

    ArregloDinamico<Album>& GETAlbumes();
    ArregloDinamico<Mensaje>& GETMensajesRecibidos();
    const ArregloDinamico<Album>& GETAlbumes() const;
    const ArregloDinamico<int>& GETIdsAmigos() const;
    const ArregloDinamico<SolicitudAmistad>& GETSolicitudes() const;
    const ArregloDinamico<Mensaje>& GETMensajesRecibidos() const;
};

#endif // USUARIO_H
