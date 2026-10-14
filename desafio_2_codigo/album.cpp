#include "album.h"

Album::Album(){
    nombreAlbum= Cadena("Sin nombre");
    rutaAlmacenamiento= Cadena("Sin ruta");
    Privacidad= Cadena("Publico");
}

Album::Album(Cadena nombre, Cadena ruta, Cadena privacidad){
    nombreAlbum= nombre;
    rutaAlmacenamiento= ruta;
    Privacidad= privacidad;
}

Album::Album(const Album& copia){
    nombreAlbum = copia.nombreAlbum;
    rutaAlmacenamiento = copia.rutaAlmacenamiento;
    Privacidad = copia.Privacidad;
    fotos = copia.fotos;
}

Album& Album::operator=(const Album& copia) {
    if (this == &copia){
        return *this;
    }
    nombreAlbum = copia.nombreAlbum;
    rutaAlmacenamiento = copia.rutaAlmacenamiento;
    Privacidad = copia.Privacidad;
    fotos = copia.fotos;
    return *this;
}


void Album::agregarFoto(const Foto& foto){
    fotos.agregar(foto);
}

ArregloDinamico<Foto>& Album::GETFotos(){
    return fotos;
}

Cadena Album::GETprivacidad() const{
    return Privacidad;
}

Cadena Album::GETNombre() const{
    return nombreAlbum;
}