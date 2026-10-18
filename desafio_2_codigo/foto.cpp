#include "foto.h"

Foto::Foto() {
    fechaCaptura= Cadena("Sin fecha");
    tamanioBytes=0;
    meGusta=0;
    rutaArchivo= Cadena("Sin ruta");
}

Foto::Foto(Cadena fecha, int tamanio, Cadena ruta, int likes){
    fechaCaptura= fecha;
    tamanioBytes= tamanio;
    meGusta= (likes > 0) ? likes : 0;
    rutaArchivo=ruta;
}


void Foto::incrementarMeGusta(){
    meGusta++;
}

void Foto::decrementarMeGusta(){
    if (meGusta>0){
        meGusta--;
    }
}

Cadena Foto::GETRuta() const{
    return rutaArchivo;
}

int Foto::GETMeGusta() const{
    return meGusta;
}

Cadena Foto::GETFecha() const{
    return fechaCaptura;
}

int Foto::GETTamanio() const{
    return tamanioBytes;
}
