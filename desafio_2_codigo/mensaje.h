#ifndef MENSAJE_H
#define MENSAJE_H

#include "cadena.h"

class Mensaje{
private:
    Cadena Emisor;
    Cadena Receptor;
    Cadena Contenido;
    Cadena FechaEnvio;
    bool Leido;

public:
    Mensaje();
    Mensaje(Cadena emisor, Cadena receptor, Cadena contenido, Cadena fechaenvio);

    void marcarLeido();
    bool esLeido() const;
    Cadena GETfecha() const;
    Cadena GETEmisor() const;
    Cadena GETcontenido() const;

    bool operator<(const Mensaje& copia) const;
};

#endif // MENSAJE_H
