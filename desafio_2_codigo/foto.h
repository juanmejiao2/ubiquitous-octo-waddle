#ifndef FOTO_H
#define FOTO_H

#include "cadena.h"

class Foto{
private:
    Cadena fechaCaptura;
    int tamanioBytes;
    int meGusta;
    Cadena rutaArchivo;

public:
    Foto();
    Foto(Cadena fecha, int tamanio, Cadena ruta);

    void incrementarMeGusta();
    void decrementarMeGusta();
    Cadena GETRuta() const;
    int GETMeGusta() const;
};

#endif // FOTO_H
