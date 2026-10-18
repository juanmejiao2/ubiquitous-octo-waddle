#ifndef CADENA_H
#define CADENA_H

class Cadena{
private:
    char* datos;
    int longitud;

public:
    Cadena();
    Cadena(const char* str);
    Cadena(const Cadena& copia);
    ~Cadena();
    Cadena& operator=(const Cadena& otra);
    bool operator==(const Cadena& otra) const;
    bool operator<(const Cadena& otra) const;
    int GETLongitud() const;
    const char* GETDatos() const;
};

#endif // CADENA_H
