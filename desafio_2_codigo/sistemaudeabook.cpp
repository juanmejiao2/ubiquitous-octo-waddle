#include "sistemaudeabook.h"
#include <iostream>
#include <chrono>

using namespace std;

SistemaUdeaBook::SistemaUdeaBook()
    : usuarios(), matrizAmistades(), medidor(),
    usuarioAutenticadoIndex(-1), yaAlternoFotos(false),
    fotosMostradas(), generador(std::random_device{}()){
    }



SistemaUdeaBook::SistemaUdeaBook(const SistemaUdeaBook& otro)
    : usuarios(otro.usuarios), matrizAmistades(otro.matrizAmistades),
    medidor(otro.medidor), usuarioAutenticadoIndex(otro.usuarioAutenticadoIndex),
    yaAlternoFotos(otro.yaAlternoFotos), fotosMostradas(otro.fotosMostradas),
    generador(otro.generador){
}

SistemaUdeaBook& SistemaUdeaBook::operator=(const SistemaUdeaBook& otro) {
    if (this != &otro) {
        usuarios = otro.usuarios;
        matrizAmistades = otro.matrizAmistades;
        medidor = otro.medidor;
        usuarioAutenticadoIndex = otro.usuarioAutenticadoIndex;
        yaAlternoFotos = otro.yaAlternoFotos;
        fotosMostradas= otro.fotosMostradas;
        generador= otro.generador;
    }
    return *this;
}

SistemaUdeaBook::~SistemaUdeaBook() {
    usuarioAutenticadoIndex = -1;
    yaAlternoFotos = false;
}

Cadena SistemaUdeaBook::leerCadenaDesdeArchivo(ifstream& archivo, char delimitador) {
    char buffer[513];
    int pos = 0;
    char c;
    while (archivo.get(c)) {
        if (c == delimitador || c == '\n' || c == '\r') {
            if (c == '\r' && archivo.peek() == '\n') archivo.get();
            break;
        }
        if (pos < 512) {
            buffer[pos++] = c;
        }
    }
    buffer[pos] = '\0';
    return Cadena(buffer);
}

Cadena SistemaUdeaBook::fechaActual() const {
    using namespace std::chrono;
    long long seg = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    seg -= 5 * 3600;                       // Colombia = UTC-5
    long long z = seg / 86400 + 719468;    // dias desde 1970 -> fecha del calendario
    long long era = (z >= 0 ? z : z - 146096) / 146097;
    long long doe = z - era * 146097;
    long long yoe = (doe - doe/1460 + doe/36524 - doe/146096) / 365;
    long long doy = doe - (365*yoe + yoe/4 - yoe/100);
    long long mp  = (5*doy + 2) / 153;
    int dia  = doy - (153*mp + 2)/5 + 1;
    int mes  = mp < 10 ? mp + 3 : mp - 9;
    int anio = yoe + era*400 + (mes <= 2 ? 1 : 0);

    char t[11] = { char('0'+anio/1000), char('0'+anio/100%10), char('0'+anio/10%10), char('0'+anio%10), '-',
                  char('0'+mes/10), char('0'+mes%10), '-',
                  char('0'+dia/10), char('0'+dia%10), '\0' };
    return Cadena(t);
}


bool SistemaUdeaBook::fechaValida(const Cadena& fecha) const {
    if (fecha.GETLongitud() != 10) return false;
    const char* d = fecha.GETDatos();
    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (d[i] != '-') return false;
        } else if (d[i] < '0' || d[i] > '9') {
            return false;
        }
    }
    int mes = (d[5]-'0')*10 + (d[6]-'0');
    int dia = (d[8]-'0')*10 + (d[9]-'0');
    return mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31;
}

int SistemaUdeaBook::leerEntero() {
    int valor;
    if (!(cin >> valor)) {
        if (cin.eof()) return -1;
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return valor;
}

void SistemaUdeaBook::cargarDatos() {
    medidor.registrarIteracion();
    ifstream archivo("datos.txt");
    if (!archivo.is_open()){
        cout << "[ERROR] No se pudo abrir el archivo datos.txt\n";
    return;
    } else {
    cout << "[EXITO] Archivo datos.txt abierto correctamente\n";
    }

    char bufferTipo[64];
    archivo.width(64);
    while (archivo >> bufferTipo) {
        medidor.registrarIteracion();
        Cadena tipo(bufferTipo);

        if (tipo == Cadena("[USUARIOS]")) {
            int cantidad = 0;
            archivo >> cantidad;
            archivo.ignore(10000,'\n');
            for (int i = 0; i < cantidad; ++i) {
                medidor.registrarIteracion();
                Cadena nom = leerCadenaDesdeArchivo(archivo, ';');
                Cadena fnac = leerCadenaDesdeArchivo(archivo, ';');
                Cadena corr = leerCadenaDesdeArchivo(archivo, ';');
                Cadena foto = leerCadenaDesdeArchivo(archivo, ';');
                Cadena pass = leerCadenaDesdeArchivo(archivo, ';');
                Cadena ciud = leerCadenaDesdeArchivo(archivo, ';');
                Cadena pais = leerCadenaDesdeArchivo(archivo, ';');
                Cadena fins = leerCadenaDesdeArchivo(archivo, '\n');

                Usuario u(nom, fnac, corr, foto, pass, ciud, pais, fins);
                usuarios.agregar(u);
            }
            matrizAmistades = RedAmigos(usuarios.GETTamanio());
        }
        else if (tipo == Cadena("[MATRIZ]")) {
            int totalU = 0;
            archivo >> totalU;

            if (totalU <= 0 || totalU > 5000) {
                return;
            }

            matrizAmistades = RedAmigos(totalU);
            for (int i = 0; i < totalU; ++i) {
                for (int j = 0; j < totalU; ++j) {
                    int val = 0;

                    if (!(archivo >> val)) {
                        break;
                    }

                    if (val == 1) {
                        matrizAmistades.registrarAmistad(i, j);
                    }
                }
            }
        }
    else if (tipo == Cadena("[SOLICITUDES]")) {
        int cantidad = 0;
        archivo >> cantidad;
        archivo.ignore(10000, '\n');
        for (int i = 0; i < cantidad; ++i) {
            medidor.registrarIteracion();
            int idx = -1;
            archivo >> idx;
            archivo.ignore(1);
            Cadena emisor = leerCadenaDesdeArchivo(archivo, ';');
            Cadena estado = leerCadenaDesdeArchivo(archivo, '\n');
            if (idx >= 0 && idx < usuarios.GETTamanio()) {
                SolicitudAmistad sol(emisor, usuarios[idx].GETNombreUsuario());
                sol.cambiarEstado(estado);
                usuarios[idx].recibirSolicitud(sol);
            }
        }
    }
    else if (tipo == Cadena("[MENSAJES]")) {
        int cantidad = 0;
        archivo >> cantidad;
        archivo.ignore(10000, '\n');
        for (int i = 0; i < cantidad; ++i) {
            medidor.registrarIteracion();
            int idx = -1, leido = 0;
            archivo >> idx;
            archivo.ignore(1);
            Cadena emisor = leerCadenaDesdeArchivo(archivo, ';');
            Cadena fecha = leerCadenaDesdeArchivo(archivo, ';');
            archivo >> leido;
            archivo.ignore(1);
            Cadena contenido = leerCadenaDesdeArchivo(archivo, '\n');
            if (idx >= 0 && idx < usuarios.GETTamanio()) {
                Mensaje msj(emisor, usuarios[idx].GETNombreUsuario(), contenido, fecha);
                if (leido == 1) msj.marcarLeido();
                usuarios[idx].recibirMensaje(msj);
            }
        }
    }
    else if (tipo == Cadena("[ALBUMES]")) {
        int cantidad = 0;
        archivo >> cantidad;
        archivo.ignore(10000, '\n');
        for (int i = 0; i < cantidad; ++i) {
            medidor.registrarIteracion();
            int idx = -1, numFotos = 0;
            archivo >> idx;
            archivo.ignore(1);
            Cadena nombre = leerCadenaDesdeArchivo(archivo, ';');
            Cadena privacidad = leerCadenaDesdeArchivo(archivo, ';');
            Cadena ruta = leerCadenaDesdeArchivo(archivo, ';');
            archivo >> numFotos;
            archivo.ignore(10000, '\n');

            Album album(nombre, ruta, privacidad);
            for (int f = 0; f < numFotos; ++f) {
                medidor.registrarIteracion();
                int tamanio = 0, likes = 0;
                Cadena fechaFoto = leerCadenaDesdeArchivo(archivo, ';');
                archivo >> tamanio;
                archivo.ignore(1);
                archivo >> likes;
                archivo.ignore(1);
                Cadena rutaFoto = leerCadenaDesdeArchivo(archivo, '\n');
                album.agregarFoto(Foto(fechaFoto, tamanio, rutaFoto, likes));
            }
            if (idx >= 0 && idx < usuarios.GETTamanio()) {
                usuarios[idx].agregarAlbum(album);
                }
            }
        }
    archivo.width(64);
   }
archivo.close();
}



void SistemaUdeaBook::guardarDatos() {
    medidor.registrarIteracion();
    ofstream archivo("datos.txt");
    if (!archivo.is_open()) return;

    int totalUsuarios = usuarios.GETTamanio();
    archivo << "[USUARIOS]\n" << totalUsuarios << "\n";
    for (int i = 0; i < totalUsuarios; ++i) {
        medidor.registrarIteracion();
        archivo << usuarios[i].GETNombreUsuario().GETDatos() << ";"
                << usuarios[i].GETFechaNacimiento().GETDatos() << ";"
                << usuarios[i].GETCorreo().GETDatos() << ";"
                << usuarios[i].GETFotoPerfil().GETDatos() << ";"
                << usuarios[i].GETContrasena().GETDatos() << ";"
                << usuarios[i].GETCiudad().GETDatos() << ";"
                << usuarios[i].GETPais().GETDatos() << ";"
                << usuarios[i].GETFechaInscripcion().GETDatos() << "\n";
    }
    int totalU = matrizAmistades.getTotalUsuarios();
    archivo << "[MATRIZ]\n" << totalU << "\n";
    for (int i = 0; i < totalU; ++i) {
        for (int j = 0; j < totalU; ++j) {
            bool amigo = matrizAmistades.sonAmigos(i, j);
            archivo << (amigo ? 1 : 0) << (j == totalU - 1 ? "" : " ");
        }
        archivo << "\n";
    }

    //Solicitudes
    int totalSol = 0;
    for (int i = 0; i < totalUsuarios; ++i) {
        totalSol += usuarios[i].GETSolicitudes().GETTamanio();
    }
    archivo << "[SOLICITUDES]\n" << totalSol << "\n";
    for (int i = 0; i < totalUsuarios; ++i) {
        ArregloDinamico<SolicitudAmistad>& sols = usuarios[i].GETSolicitudes();
        for (int s = 0; s < sols.GETTamanio(); ++s) {
            medidor.registrarIteracion();
            archivo << i << ";" << sols[s].GETEmisor().GETDatos() << ";"
                    << sols[s].GETEstado().GETDatos() << "\n";
        }
    }

    //Mensajes
    int totalMsj = 0;
    for (int i = 0; i < totalUsuarios; ++i) {
        totalMsj += usuarios[i].GETMensajesRecibidos().GETTamanio();
    }
    archivo << "[MENSAJES]\n" << totalMsj << "\n";
    for (int i = 0; i < totalUsuarios; ++i) {
        ArregloDinamico<Mensaje>& msjs = usuarios[i].GETMensajesRecibidos();
        for (int m = 0; m < msjs.GETTamanio(); ++m) {
            medidor.registrarIteracion();
            archivo << i << ";" << msjs[m].GETEmisor().GETDatos() << ";"
                    << msjs[m].GETfecha().GETDatos() << ";"
                    << (msjs[m].esLeido() ? 1 : 0) << ";"
                    << msjs[m].GETcontenido().GETDatos() << "\n";
        }
    }

    //albumes y fotos
    int totalAlb = 0;
    for (int i = 0; i < totalUsuarios; ++i) {
        totalAlb += usuarios[i].GETAlbumes().GETTamanio();
    }
    archivo << "[ALBUMES]\n" << totalAlb << "\n";
    for (int i = 0; i < totalUsuarios; ++i) {
        ArregloDinamico<Album>& albs = usuarios[i].GETAlbumes();
        for (int a = 0; a < albs.GETTamanio(); ++a) {
            medidor.registrarIteracion();
            ArregloDinamico<Foto>& fotos = albs[a].GETFotos();
            archivo << i << ";" << albs[a].GETNombre().GETDatos() << ";"
                    << albs[a].GETprivacidad().GETDatos() << ";"
                    << albs[a].GETRuta().GETDatos() << ";"
                    << fotos.GETTamanio() << "\n";
            for (int f = 0; f < fotos.GETTamanio(); ++f) {
                medidor.registrarIteracion();
                archivo << fotos[f].GETFecha().GETDatos() << ";"
                        << fotos[f].GETTamanio() << ";"
                        << fotos[f].GETMeGusta() << ";"
                        << fotos[f].GETRuta().GETDatos() << "\n";
            }
        }
    }
    archivo.close();
}


bool SistemaUdeaBook::iniciarSesion(Cadena correo, Cadena contrasena) {
    medidor.registrarIteracion();
    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETCorreo() == correo && usuarios[i].validarContrasenia(contrasena)) {
            usuarioAutenticadoIndex = i;
            return true;
        }
    }
    return false;
}

bool SistemaUdeaBook::registrarUsuario(const Usuario& nuevoUsuario){
    medidor.registrarIteracion();
    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == nuevoUsuario.GETNombreUsuario() ||
            usuarios[i].GETCorreo() == nuevoUsuario.GETCorreo() ){
            return false;
        }
    }
    usuarios.agregar(nuevoUsuario);
    matrizAmistades.redimensionar(usuarios.GETTamanio());
    return true;
}

void SistemaUdeaBook::mostrarMejoresAmigos() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
        yaAlternoFotos=false;
        cout << "\n--- MEJORES AMIGOS ---" << endl;
        mostrarFotosAmigos(false);
}

void SistemaUdeaBook::mostrarFotosAmigos(bool esActualizacion) {
    int yo = usuarioAutenticadoIndex;
    int total = usuarios.GETTamanio();
    ArregloDinamico<int> candidatos;
    ArregloDinamico<int> pesos;
    int pesoTotal = 0;
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (!matrizAmistades.sonAmigos(yo, i)) continue;
        if (esActualizacion) {
            bool yaMostrado = false;
            for (int m = 0; m < fotosMostradas.GETTamanio(); ++m) {
                medidor.registrarIteracion();
                if (fotosMostradas[m] == i) { yaMostrado = true; break; }
            }
            if (yaMostrado) continue;
        }
        int comunes = matrizAmistades.contarAmigosEnComun(yo, i);
        medidor.registrarIteracion(total);
        int peso = 10;
        if (comunes > 20) peso = 35;
        else if (comunes > 10) peso = 25;
        candidatos.agregar(i);
        pesos.agregar(peso);
        pesoTotal += peso;
    }
    if (candidatos.GETTamanio() == 0) {
        if (esActualizacion) cout << "No hay mas amigos con fotos distintas para mostrar." << endl;
        else cout << "Aun no tienes amigos para mostrar." << endl;
        return;
    }
    int aMostrar = candidatos.GETTamanio() < 3 ? candidatos.GETTamanio() : 3;
    ArregloDinamico<int> elegidos;
    for (int k = 0; k < aMostrar; ++k) {
        std::uniform_int_distribution<int> distribucion(1, pesoTotal);
        int sorteo = distribucion(generador);
        int acumulado = 0;
        for (int c = 0; c < candidatos.GETTamanio(); ++c) {
            medidor.registrarIteracion();
            acumulado += pesos[c];
            if (acumulado >= sorteo) {
                elegidos.agregar(candidatos[c]);
                pesoTotal -= pesos[c];
                pesos[c] = 0;
                break;
            }
        }
    }
    for (int e = 0; e < elegidos.GETTamanio(); ++e) {
        int idx = elegidos[e];
        cout << " " << (e + 1) << ". " << usuarios[idx].GETNombreUsuario().GETDatos()
             << " -> " << usuarios[idx].GETFotoPerfil().GETDatos() << endl;
    }
    if (!esActualizacion) {
        fotosMostradas = elegidos;
        cout << "(Puedes actualizar estas fotos una sola vez con la opcion 8)" << endl;
    }
}

void SistemaUdeaBook::cambiarFotosPerfil() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    if (yaAlternoFotos) {
        cout << "[ERROR] Ya actualizaste las fotos una vez en esta sesion." << endl;
        return;
    }
    yaAlternoFotos = true;
    cout << "\n--- NUEVAS FOTOS DE MEJORES AMIGOS ---" << endl;
    mostrarFotosAmigos(true);
}

void SistemaUdeaBook::enviarSolicitudAmistad(Cadena receptor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();

    // 1. Validar si se envía a sí mismo
    if (emisor == receptor) {
        cout << "[ERROR] No puedes enviarte una solicitud a ti mismo." << endl;
        return;
    }

    int idxReceptor = -1;
    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
            idxReceptor = i;
            break;
        }
    }

    if (idxReceptor == -1) {
        cout << "[ERROR] Usuario receptor no encontrado." << endl;
        return;
    }

    // 2. Validar si ya son amigos
    if (matrizAmistades.sonAmigos(usuarioAutenticadoIndex, idxReceptor)) {
        cout << "[ERROR] Ya eres amigo de este usuario." << endl;
        return;
    }

    // 3. Validar si ya existe solicitud pendiente
    ArregloDinamico<SolicitudAmistad>& recSols = usuarios[idxReceptor].GETSolicitudes();
    for (int s = 0; s < recSols.GETTamanio(); ++s) {
        if (recSols[s].GETEmisor() == emisor && recSols[s].GETEstado() == Cadena("Pendiente")) {
            cout << "[ERROR] Ya enviaste una solicitud pendiente a este usuario." << endl;
            return;
        }
    }

    // 4. Validar si el receptor ya me envio una solicitud a mi
    ArregloDinamico<SolicitudAmistad>& misSols = usuarios[usuarioAutenticadoIndex].GETSolicitudes();
    for (int s = 0; s < misSols.GETTamanio(); ++s) {
        medidor.registrarIteracion();
        if (misSols[s].GETEmisor() == receptor && misSols[s].GETEstado() == Cadena("Pendiente")) {
            cout << "[ERROR] Ese usuario ya te envio una solicitud. Aceptala en la opcion 4." << endl;
            return;
        }
    }

    SolicitudAmistad sol(emisor, receptor);
    usuarios[idxReceptor].recibirSolicitud(sol);
    cout << "Solicitud enviada a " << receptor.GETDatos() << endl;
}

void SistemaUdeaBook::aceptarSolicitudAmistad(Cadena emisor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<SolicitudAmistad>& solRecibidas = usuarios[usuarioAutenticadoIndex].GETSolicitudes();
    int total = solRecibidas.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (solRecibidas[i].GETEmisor() == emisor && solRecibidas[i].GETEstado() == Cadena("Pendiente")) {
            solRecibidas[i].cambiarEstado(Cadena("Aceptada"));
            int indiceEmisor = -1;
            for (int u = 0; u < usuarios.GETTamanio(); ++u) {
                if (usuarios[u].GETNombreUsuario() == emisor) {
                    indiceEmisor = u;
                    break;
                }
            }
            if (indiceEmisor != -1) {
                matrizAmistades.registrarAmistad(usuarioAutenticadoIndex, indiceEmisor);
            }

            cout << "Solicitud de " << emisor.GETDatos() << " aceptada exitosamente." << endl;
            return;
        }
    }
    cout << "No se encontro solicitud pendiente de ese usuario." << endl;
}

void SistemaUdeaBook::verSugerenciasAmistad(int k) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    if (k < 1 || k > 20) {
        cout << "[ERROR] K debe estar entre 1 y 20." << endl;
        return;
    }
    int yo = usuarioAutenticadoIndex;
    int total = usuarios.GETTamanio();
    ArregloDinamico<int> candidatos;
    ArregloDinamico<int> comunes;
    for (int c = 0; c < total; ++c) {
        medidor.registrarIteracion();
        if (c == yo || matrizAmistades.sonAmigos(yo, c)) continue;
        int enComun = matrizAmistades.contarAmigosEnComun(yo, c);
        medidor.registrarIteracion(total);
        if (enComun > 0) {
            candidatos.agregar(c);
            comunes.agregar(enComun);
        }
    }
    if (candidatos.GETTamanio() == 0) {
        cout << "No hay sugerencias de amistad por ahora." << endl;
        return;
    }
    int mostrar = candidatos.GETTamanio() < k ? candidatos.GETTamanio() : k;
    for (int p = 0; p < mostrar; ++p) {
        int mejor = p;
        for (int q = p + 1; q < candidatos.GETTamanio(); ++q) {
            medidor.registrarIteracion();
            if (comunes[q] > comunes[mejor]) mejor = q;
        }
        int tmp = candidatos[p]; candidatos[p] = candidatos[mejor]; candidatos[mejor] = tmp;
        tmp = comunes[p]; comunes[p] = comunes[mejor]; comunes[mejor] = tmp;
    }
    cout << "\n--- " << mostrar << " SUGERENCIAS DE AMISTAD ---" << endl;
    for (int p = 0; p < mostrar; ++p) {
        cout << " " << (p + 1) << ". " << usuarios[candidatos[p]].GETNombreUsuario().GETDatos()
        << " (" << comunes[p] << " amigos en comun)" << endl;
    }
    cout << "Numero de la sugerencia para enviar solicitud (0 para ninguna): ";
    int sel = leerEntero();
    if (sel >= 1 && sel <= mostrar) {
        enviarSolicitudAmistad(usuarios[candidatos[sel - 1]].GETNombreUsuario());
    } else if (sel != 0) {
        cout << "[ERROR] Opcion no valida." << endl;
    }
}

void SistemaUdeaBook::visitarPerfilAmigo(Cadena nombreAmigo) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    int idx = -1;
    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == nombreAmigo) { idx = i; break; }
    }
    if (idx == -1) {
        cout << "El usuario no existe." << endl;
        return;
    }
    if (idx == usuarioAutenticadoIndex) {
        cout << "[ERROR] Ese es tu propio perfil." << endl;
        return;
    }
    if (!matrizAmistades.sonAmigos(usuarioAutenticadoIndex, idx)) {
        cout << "\n[ACCESO DENEGADO] No puedes ver el perfil de " << nombreAmigo.GETDatos() << " porque no son amigos." << endl;
        return;
    }
    cout << "\n=== PERFIL DE " << nombreAmigo.GETDatos() << " ===" << endl;
    cout << "Ciudad: " << usuarios[idx].GETCiudad().GETDatos() << endl;
    cout << "Pais: " << usuarios[idx].GETPais().GETDatos() << endl;

    ArregloDinamico<Album>& albumes = usuarios[idx].GETAlbumes();
    ArregloDinamico<int> visibles;
    for (int a = 0; a < albumes.GETTamanio(); ++a) {
        medidor.registrarIteracion();
        Cadena priv = albumes[a].GETprivacidad();
        if (priv == Cadena("Publico") || priv == Cadena("Amigos")) {
            visibles.agregar(a);
            cout << " " << visibles.GETTamanio() << ". " << albumes[a].GETNombre().GETDatos()
                 << " (" << priv.GETDatos() << ", " << albumes[a].GETFotos().GETTamanio() << " fotos)" << endl;
        }
    }
    if (visibles.GETTamanio() == 0) {
        cout << "Este amigo no tiene albumes visibles." << endl;
        return;
    }
    cout << "Seleccione un album (0 para volver): ";
    int sel = leerEntero();
    if (sel < 1 || sel > visibles.GETTamanio()) return;
    Album& album = albumes[visibles[sel - 1]];
    ArregloDinamico<Foto>& fotos = album.GETFotos();
    int n = fotos.GETTamanio();
    if (n == 0) {
        cout << "El album no tiene fotos." << endl;
        return;
    }
    ArregloDinamico<int> leDiLike(n);
    for (int f = 0; f < n; ++f) leDiLike.agregar(0);
    int actual = 0;
    while (true) {
        medidor.registrarIteracion();
        cout << "\n[" << album.GETNombre().GETDatos() << "] Foto " << (actual + 1) << "/" << n << endl;
        cout << " " << fotos[actual].GETRuta().GETDatos() << endl;
        cout << " Likes: " << fotos[actual].GETMeGusta() << (leDiLike[actual] ? "  (te gusta)" : "") << endl;
        cout << " 1. Siguiente  2. Anterior  3. Dar/Quitar like  0. Salir del album" << endl;
        cout << "Opcion: ";
        int op = leerEntero();
        if (op == 0 || cin.eof()) break;
        if (op == 1) {
            actual = (actual + 1) % n;
        } else if (op == 2) {
            actual = (actual - 1 + n) % n;
        } else if (op == 3) {
            if (leDiLike[actual]) {
                fotos[actual].decrementarMeGusta();
                leDiLike[actual] = 0;
                cout << "Like quitado." << endl;
            } else {
                fotos[actual].incrementarMeGusta();
                leDiLike[actual] = 1;
                cout << "Like agregado." << endl;
            }
        } else {
            cout << "[ERROR] Opcion no valida." << endl;
        }
    }
}

void SistemaUdeaBook::enviarMensaje(Cadena receptor, Cadena contenido) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    if (contenido.GETLongitud() == 0) {
        cout << "[ERROR] No puedes enviar un mensaje vacio." << endl;
        return;
    }
    if (contenido.GETLongitud() > 512) {
        cout << "[ERROR] El mensaje no puede superar 512 caracteres." << endl;
        return;
    }

    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
            if (!matrizAmistades.sonAmigos(usuarioAutenticadoIndex, i)) {
                cout << "[ERROR] Solo puedes enviar mensajes a tus amigos." << endl;
                return;
            }
            Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();
            Mensaje msj(emisor, receptor, contenido, fechaActual());
            usuarios[i].recibirMensaje(msj);
            cout << "Mensaje enviado a " << receptor.GETDatos() << endl;
            return;
        }
    }
    cout << "Receptor no encontrado." << endl;
}

void SistemaUdeaBook::leerNuevosMensajes() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].GETMensajesRecibidos();
    int total = recibidos.GETTamanio();
    cout << "\n--- MENSAJES RECIBIDOS ---" << endl;
    bool hayNuevos = false;
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (!recibidos[i].esLeido()) {
            cout << "De: " << recibidos[i].GETEmisor().GETDatos()
            << " | Texto: " << recibidos[i].GETcontenido().GETDatos() << endl;
            recibidos[i].marcarLeido();
            hayNuevos = true;
        }
    }
    if (!hayNuevos) cout <<"no tienes mensajes nuevos. "<<endl;
}

void SistemaUdeaBook::buscarMensajesPorFecha(Cadena inicio, Cadena fin) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    if (!fechaValida(inicio) || !fechaValida(fin)) {
        cout << "[ERROR] Las fechas deben tener el formato aaaa-mm-dd (ej: 2026-08-15)." << endl;
        return;
    }
    if (fin < inicio) {
        cout << "[ERROR] La fecha de inicio no puede ser posterior a la fecha de fin." << endl;
        return;
    }
    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].GETMensajesRecibidos();
    int total = recibidos.GETTamanio();
    int encontrados = 0;
    cout << "\n--- MENSAJES DEL " << inicio.GETDatos() << " AL " << fin.GETDatos() << " ---" << endl;
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        Cadena fecha = recibidos[i].GETfecha();
        if (!(fecha < inicio) && !(fin < fecha)) {
            cout << "[" << fecha.GETDatos() << "] De: " << recibidos[i].GETEmisor().GETDatos()
            << " | " << recibidos[i].GETcontenido().GETDatos() << endl;
            encontrados++;
        }
    }
    if (encontrados == 0) cout << "No hay mensajes en ese rango." << endl;
    else cout << "Total: " << encontrados << " mensajes." << endl;
}

void SistemaUdeaBook::ejecutarMenu() {
    int opcion = 0;
    char buffer1[256], buffer2[256], buffer3[256];

    while (opcion != 3) {
        cout << "\n========================================" << endl;
        cout << "        SISTEMA UDEABOOK V1.0           " << endl;
        cout << "========================================" << endl;
        if (usuarioAutenticadoIndex == -1) {
            cout << " 1. Iniciar Sesion" << endl;
            cout << " 2. Registrar Nuevo Usuario" << endl;
            cout << " 3. Salir y Guardar" << endl;
            cout << "Seleccione una opcion: ";

            if (!(cin >> opcion)) {
                if (cin.eof()) break;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[ERROR] Por favor ingresa un numero valido.\n";
                continue;
            }
            cin.ignore(10000, '\n');

            if (opcion == 1) {
                cout << "Correo: "; cin.width(256); cin >> buffer1;
                cout << "Contrasena: "; cin.width(256); cin >> buffer2;
                if (iniciarSesion(Cadena(buffer1), Cadena(buffer2))) {
                    cout << "\n[OK] Sesion iniciada como " << usuarios[usuarioAutenticadoIndex].GETNombreUsuario().GETDatos() << endl;
                    mostrarMejoresAmigos();
                } else {
                    cout << "\n[ERROR] Credenciales incorrectas." << endl;
                }
            } else if (opcion == 2) {
                cout << "Nombre de Usuario: "; cin.width(256); cin >> buffer1;
                cout << "Correo: "; cin.width(256); cin >> buffer2;
                cout << "Contrasena: "; cin.width(256); cin >> buffer3;
                Usuario nuevo(Cadena(buffer1), Cadena("2000-01-01"), Cadena(buffer2),
                              Cadena("default.jpg"), Cadena(buffer3), Cadena("Medellin"),
                              Cadena("Colombia"), fechaActual());
                if (registrarUsuario(nuevo)) {
                    guardarDatos();
                    cout << "\n[OK] Usuario registrado exitosamente." << endl;
                } else {
                    cout << "\n[ERROR] El usuario o correo ya existe." << endl;
                }
            }
        } else {
            cout << "Usuario conectado: " << usuarios[usuarioAutenticadoIndex].GETNombreUsuario().GETDatos() << endl;
            cout << " 1. Enviar Mensaje" << endl;
            cout << " 2. Leer Nuevos Mensajes" << endl;
            cout << " 3. Buscar Mensajes por Fecha" << endl;
            cout << " 4. Enviar Solicitud de Amistad" << endl;
            cout << " 5. Aceptar Solicitud de Amistad" << endl;
            cout << " 6. Visitar Perfil de Amigo" << endl;
            cout << " 7. Ver Sugerencias de Amistad" << endl;
            cout << " 8. Actualizar Fotos de Mejores Amigos" << endl;
            cout << " 9. Ver Reporte de Recursos (Medidor)" << endl;
            cout << " 10. Cerrar Sesion" << endl;
            cout << "Seleccione una opcion: ";

            int subopcion;
            if (!(cin >> subopcion)) {
                if (cin.eof()) break;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[ERROR] Por favor ingresa un numero valido.\n";
                continue;
            }
            cin.ignore(10000, '\n');

            if (subopcion == 1) {
                char bufferMsj[514];
                cout << "Destinatario: ";
                cin.width(256); cin >> buffer1;
                cin.ignore(10000, '\n');
                cout << "Mensaje (max 512 caracteres): ";
                cin.getline(bufferMsj, 514);
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[ERROR] El mensaje no puede superar 512 caracteres." << endl;
                } else {
                    enviarMensaje(Cadena(buffer1), Cadena(bufferMsj));
                    guardarDatos();
                }
            } else if (subopcion == 2) {
                leerNuevosMensajes();
                guardarDatos();
            } else if (subopcion == 3) {
                cout << "Fecha de inicio (aaaa-mm-dd): "; cin.width(256); cin >> buffer1;
                cout << "Fecha de fin (aaaa-mm-dd): "; cin.width(256); cin >> buffer2;
                cin.ignore(10000, '\n');
                buscarMensajesPorFecha(Cadena(buffer1), Cadena(buffer2));
            } else if (subopcion == 4) {
                cout << "Usuario a solicitar: "; cin.width(256); cin >> buffer1;
                cin.ignore(10000, '\n');
                enviarSolicitudAmistad(Cadena(buffer1));
                guardarDatos();
            } else if (subopcion == 5) {
                cout << "\n--- TUS SOLICITUDES PENDIENTES ---" << endl;
                ArregloDinamico<SolicitudAmistad>& misSols = usuarios[usuarioAutenticadoIndex].GETSolicitudes();
                int totalSols = misSols.GETTamanio();
                bool hayPendientes = false;
                for (int s = 0; s < totalSols; ++s) {
                    if (misSols[s].GETEstado() == Cadena("Pendiente")) {
                        cout << " - De: " << misSols[s].GETEmisor().GETDatos() << endl;
                        hayPendientes = true;
                    }
                }
                if (!hayPendientes) {
                    cout << "No tienes solicitudes pendientes." << endl;
                } else {
                    cout << "Ingrese el nombre del usuario que le envio la solicitud: ";
                    cin.width(256); cin >> buffer1;
                    cin.ignore(10000, '\n');
                    aceptarSolicitudAmistad(Cadena(buffer1));
                    guardarDatos();
                }
            } else if (subopcion == 6) {
                cout << "Nombre del amigo: "; cin.width(256); cin >> buffer1;
                cin.ignore(10000, '\n');
                visitarPerfilAmigo(Cadena(buffer1));
                guardarDatos();
            } else if (subopcion == 7) {
                cout << "Cuantas sugerencias quieres ver (1 a 20): ";
                int k = leerEntero();
                verSugerenciasAmistad(k);
                guardarDatos();
            } else if (subopcion == 8) {
                cambiarFotosPerfil();
            } else if (subopcion == 9) {
                size_t heapTotal = 0;
                int totalu = matrizAmistades.getTotalUsuarios();
                if (totalu > 0) {
                    heapTotal += (totalu * totalu * sizeof(bool));
                }
                int numUsuarios = usuarios.GETTamanio();
                heapTotal += (numUsuarios * sizeof(Usuario));
                medidor.setMemoriaHeap(heapTotal);
                medidor.setMemoriaStack(sizeof(*this));
                medidor.reportarRecursos();
            } else if (subopcion == 10) {
                usuarioAutenticadoIndex = -1;
                guardarDatos();
                cout << "\nSesion cerrada." << endl;
            } else {
                cout << "\n[ERROR] Opcion no valida." << endl;
            }
        }
    }
}

ArregloDinamico<Usuario>& SistemaUdeaBook::getUsuarios() { return usuarios; }
RedAmigos& SistemaUdeaBook::getMatrizAmistades() { return matrizAmistades; }
MedidorRecurso& SistemaUdeaBook::getMedidor() { return medidor; }
int SistemaUdeaBook::getUsuarioAutenticadoIndex() const { return usuarioAutenticadoIndex; }
bool SistemaUdeaBook::getYaAlternoFotos() const { return yaAlternoFotos; }

void SistemaUdeaBook::setUsuarioAutenticadoIndex(int index) { usuarioAutenticadoIndex = index; }
void SistemaUdeaBook::setYaAlternoFotos(bool alterno) { yaAlternoFotos = alterno; }