#ifndef ALBUM_H
#define ALBUM_H

#include "cadena.h"
#include "foto.h"
#include "arreglodinamico.h"

class Album{
private:
    Cadena nombreAlbum;
    Cadena rutaAlmacenamiento;
    Cadena Privacidad;
    ArregloDinamico<Foto> fotos;

public:
    Album();
    Album(Cadena nombre, Cadena ruta, Cadena privacidad);

    void agregarFoto(const Foto& foto);

    ArregloDinamico<Foto>& GETFotos();
    Cadena GETprivacidad() const;
    Cadena GETNombre() const;
};

#endif // ALBUM_H
