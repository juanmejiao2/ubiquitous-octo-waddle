#include "solicitudamistad.h"

SolicitudAmistad::SolicitudAmistad() {
    Emisor = Cadena("Desconocido");
    Receptor = Cadena("Desconocido");
    Estado = Cadena("Pendiente");
}

SolicitudAmistad::SolicitudAmistad(Cadena emisor, Cadena receptor) {
    this->Emisor = emisor;
    this->Receptor = receptor;
    this->Estado = Cadena("Pendiente");
}

Cadena SolicitudAmistad::GETEmisor() const {
    return Emisor;
}

Cadena SolicitudAmistad::GETReceptor() const {
    return Receptor;
}

Cadena SolicitudAmistad::GETEstado() const {
    return Estado;
}

void SolicitudAmistad::cambiarEstado(Cadena nuevoEstado) {
    Estado = nuevoEstado;
}
