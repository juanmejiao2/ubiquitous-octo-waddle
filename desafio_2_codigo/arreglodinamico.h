#ifndef ARREGLODINAMICO_H
#define ARREGLODINAMICO_H

template<typename T>

class ArregloDinamico{
private:
    T* elementos;
    int tamanio;
    int capacidad;

    void redimensionar(){
        capacidad= capacidad*2;
        T* nuevoArreglo= new T[capacidad];
        for (int i=0;i<tamanio;i++){
            nuevoArreglo[i]=elementos[i];
        }
        delete[] elementos;
        elementos=nuevoArreglo;
    }

public:
    ArregloDinamico(int capacidadInicial=5){
        tamanio=0;
        capacidad=capacidadInicial;
        elementos= new T[capacidad];
    }

    ArregloDinamico(const ArregloDinamico& copia){
        tamanio=copia.tamanio;
        capacidad=copia.capacidad;
        elementos=new T[capacidad];
        for (int i=0;i<tamanio;i++){
            elementos[i]=copia.elementos[i];
        }
    }
    ~ArregloDinamico(){
        delete[] elementos;
    }
    ArregloDinamico& operator=(const ArregloDinamico& copia){
        if(this==&copia){
            return *this;
        }
        delete[] elementos;
        tamanio=copia.tamanio;
        capacidad=copia.capacidad;
        elementos= new T[capacidad];
        for (int i=0;i<tamanio;i++){
            elementos[i]=copia.elementos[i];
        }
        return *this;
    }
    void agregar(const T& elemento){
        if (tamanio>=capacidad){
            redimensionar();
        }
        elementos[tamanio]=elemento;
        tamanio++;
    }

    T& operator[](int indice){
        return elementos[indice];
    }

    int GETTAMANIO() const{
        return tamanio;
    }

    int GETCapacidad() const{
        return capacidad;
    }

};

#endif // ARREGLODINAMICO_H
