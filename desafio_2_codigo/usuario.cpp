#include "usuario.h"

Usuario::Usuario() {
}

Usuario::Usuario(Cadena nombreusuario, Cadena fechanacimiento, Cadena correo, Cadena fotoperfil, Cadena contrasena, Cadena ciudad, Cadena pais, Cadena fechainscripcion){
    this->NombreUsuario= nombreusuario;
    this->FechaNacimiento= fechanacimiento;
    this->Correo= correo;
    this->FotoPerfil= fotoperfil;
    this->Contrasena= contrasena;
    this->Ciudad= ciudad;
    this->Pais= pais;
    this->FechaInscripcion= fechainscripcion;
    this->NombreUsuario= nombreusuario;
}

Cadena Usuario::GETNombreUsuario() const{
    return NombreUsuario;
}

bool Usuario::validarContrasenia(Cadena pass) const{
    return true;
}

void Usuario::agregarAmigo(int idAmigo){
    idsAmigos.agregar(idAmigo);
}

void Usuario::agregarAlbum(const Album& album){
    albumes.agregar(album);
}
void Usuario::recibirMensaje(const Mensaje& mensaje) {
    mensajesRecibidos.agregar(mensaje);
}

void Usuario::recibirSolicitud(const SolicitudAmistad& solicitud) {
    solicitudes.agregar(solicitud);
}

ArregloDinamico<Album>& Usuario::GETAlbumes() {
    return albumes;
}

const ArregloDinamico<Album>& Usuario::GETAlbumes() const {
    return albumes;
}

ArregloDinamico<Mensaje>& Usuario::GETMensajesRecibidos() {
    return mensajesRecibidos;
}

const ArregloDinamico<Mensaje>& Usuario::GETMensajesRecibidos() const {
    return mensajesRecibidos;
}

const ArregloDinamico<int>& Usuario::GETIdsAmigos() const {
    return idsAmigos;
}

const ArregloDinamico<SolicitudAmistad>& Usuario::GETSolicitudes() const {
    return solicitudes;
}