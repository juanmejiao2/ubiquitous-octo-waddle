#include "cadena.h"

int calcularLargo(const char* texto){
    if(texto==nullptr) return 0;
    int len=0;
    while(texto[len] != '\0'){
        len++;
    }
    return len;
}

Cadena::Cadena(){
    longitud=0;
    datos= new char[1];
    datos[0]= '\0';
}

Cadena::Cadena(const char* str){
    if (str != nullptr){
        longitud= calcularLargo(str);
        datos=new char [longitud+1];
        for(int i=0; i<=longitud; i++){
            datos[i]=str[i];
        }
    } else{
        longitud=0;
        datos=new char[1];
        datos[0]='\0';
    }
}

Cadena::Cadena(const Cadena& copia){
    longitud= copia.longitud;
    datos= new char[longitud+1];
    for(int i=0; i<= longitud; i++){
        datos[i]= copia.datos[i];
    }
}

Cadena::~Cadena(){
    if (datos !=nullptr){
        delete[] datos;
        datos= nullptr;
    }
}

Cadena& Cadena::operator=(const Cadena& copia){
    if(this== &copia){
        return *this;
    }
    if (datos !=nullptr){
        delete[] datos;
    }
    longitud= copia.longitud;
    datos= new char[longitud+1];
    for (int i=0; i<=longitud;i++){
        datos[i]= copia.datos[i];
    }
    return *this;
}

bool Cadena::operator==(const Cadena& copia) const{
    if (longitud != copia.longitud) return false;
    for(int i=0;i<longitud; i++){
        if(datos[i]!= copia.datos[i]) return false;
    }
    return true;
}

bool Cadena::operator<(const Cadena& otra) const {
    int i = 0;
    while (i < longitud && i < otra.longitud && datos[i] == otra.datos[i]) {
        i++;
    }
    if (i == longitud || i == otra.longitud) {
        return longitud < otra.longitud;
    }
    return datos[i] < otra.datos[i];
}

int Cadena::GETLongitud() const{
    return longitud;
}
const char* Cadena::GETDatos() const{
    return datos;
}