#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H

#include "cadena.h"

class SolicitudAmistad{
private:
    Cadena Emisor;
    Cadena Receptor;
    Cadena Estado;

public:
    SolicitudAmistad();
    SolicitudAmistad(Cadena emisor, Cadena receptor);

    Cadena GETEmisor() const;
    Cadena GETReceptor() const;
    Cadena GETEstado() const;

    void cambiarEstado(Cadena nuevoEstado);
};

#endif // SOLICITUDAMISTAD_H
