#include "mensaje.h"

Mensaje::Mensaje() {
    Emisor= Cadena("Desconocido");
    Receptor= Cadena("Desconocido");
    Contenido= Cadena("");
    FechaEnvio= Cadena("Sin fecha");
    Leido=false;
}

Mensaje::Mensaje(Cadena emisor, Cadena receptor, Cadena contenido, Cadena fechaenvio){
    this->Emisor= emisor;
    this->Receptor= receptor;
    this->Contenido= contenido;
    this->FechaEnvio= fechaenvio;
    this->Leido= false;
}

void Mensaje::marcarLeido(){
    Leido=true;
}

bool Mensaje::esLeido() const{
    return Leido;
}

Cadena Mensaje::GETfecha() const{
    return FechaEnvio;
}

Cadena Mensaje::GETEmisor() const{
    return Emisor;
}

Cadena Mensaje::GETcontenido() const{
    return Contenido;
}

bool Mensaje::operator<(const Mensaje& copia) const{
    return true;
}