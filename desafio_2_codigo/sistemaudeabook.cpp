#include "sistemaudeabook.h"
#include <iostream>

using namespace std;

SistemaUdeaBook::SistemaUdeaBook()
    : usuarios(), matrizAmistades(), medidor(),
    usuarioAutenticadoIndex(-1), yaAlternoFotos(false) {
}

SistemaUdeaBook::SistemaUdeaBook(const SistemaUdeaBook& otro)
    : usuarios(otro.usuarios), matrizAmistades(otro.matrizAmistades),
    medidor(otro.medidor), usuarioAutenticadoIndex(otro.usuarioAutenticadoIndex),
    yaAlternoFotos(otro.yaAlternoFotos) {
}

SistemaUdeaBook& SistemaUdeaBook::operator=(const SistemaUdeaBook& otro) {
    if (this != &otro) {
        usuarios = otro.usuarios;
        matrizAmistades = otro.matrizAmistades;
        medidor = otro.medidor;
        usuarioAutenticadoIndex = otro.usuarioAutenticadoIndex;
        yaAlternoFotos = otro.yaAlternoFotos;
    }
    return *this;
}

SistemaUdeaBook::~SistemaUdeaBook() {
    usuarioAutenticadoIndex = -1;
    yaAlternoFotos = false;
}

Cadena SistemaUdeaBook::leerCadenaDesdeArchivo(ifstream& archivo, char delimitador) {
    char buffer[512];
    int pos = 0;
    char c;
    while (archivo.get(c)) {
        if (c == delimitador || c == '\n' || c == '\r') {
            if (c == '\r' && archivo.peek() == '\n') archivo.get();
            break;
        }
        if (pos < 511) {
            buffer[pos++] = c;
        }
    }
    buffer[pos] = '\0';
    return Cadena(buffer);
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
    while (archivo >> bufferTipo) {
        medidor.registrarIteracion();
        Cadena tipo(bufferTipo);

        if (tipo == Cadena("[USUARIOS]")) {
            int cantidad = 0;
            archivo >> cantidad;
            archivo.get();
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
            for (int i = 0; i < totalU; ++i) {
                for (int j = 0; j < totalU; ++j) {
                    int val = 0;
                    archivo >> val;
                    if (val == 1) {
                        matrizAmistades.registrarAmistad(i, j);
                    }
                }
            }
        }
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
    return true;
}

void SistemaUdeaBook::mostrarMejoresAmigos() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    cout << "\n--- MEJORES AMIGOS ---" << endl;
}

void SistemaUdeaBook::cambiarFotosPerfil() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    yaAlternoFotos = !yaAlternoFotos;
    cout << "Estado de alternancia de foto cambiado a: " << (yaAlternoFotos ? "Alterno" : "Principal") << endl;
}

void SistemaUdeaBook::enviarSolicitudAmistad(Cadena receptor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();
    SolicitudAmistad sol(emisor, receptor);

    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
            usuarios[i].recibirSolicitud(sol);
            cout << "Solicitud enviada a " << receptor.GETDatos() << endl;
            return;
        }
    }
    cout << "Usuario receptor no encontrado." << endl;
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

void SistemaUdeaBook::verSugerenciasAmistad(int idUsuario) {
    medidor.registrarIteracion();
    cout << "\n--- SUGERENCIAS DE AMISTAD PARA ID " << idUsuario << " ---" << endl;
}

void SistemaUdeaBook::visitarPerfilAmigo(Cadena nombreAmigo) {
    medidor.registrarIteracion();
    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == nombreAmigo) {
            if (i == usuarioAutenticadoIndex || matrizAmistades.sonAmigos(usuarioAutenticadoIndex, i)) {
                cout << "\n=== PERFIL DE " << nombreAmigo.GETDatos() << " ===" << endl;
                cout << "Ciudad: " << usuarios[i].GETCiudad().GETDatos() << endl;
                cout << "Pais: " << usuarios[i].GETPais().GETDatos() << endl;
            } else {
                cout << "\n[ACCESO DENEGADO] No puedes ver el perfil de " << nombreAmigo.GETDatos() << " porque no son amigos." << endl;
            }
            return;
        }
    }
    cout << "El usuario no existe." << endl;
}

void SistemaUdeaBook::enviarMensaje(Cadena receptor, Cadena contenido) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();
    Mensaje msj(emisor, receptor, contenido, Cadena("Sin fecha"));

    int total = usuarios.GETTamanio();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
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

void SistemaUdeaBook::buscarMensajesPorFecha(Cadena fecha, Cadena emisor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].GETMensajesRecibidos();
    int total = recibidos.GETTamanio();
    cout << "\n--- BUSQUEDA DE MENSAJES ---" << endl;
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (recibidos[i].GETfecha() == fecha && recibidos[i].GETEmisor() == emisor) {
            cout << "Encontrado: " << recibidos[i].GETcontenido().GETDatos() << endl;
        }
    }
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
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\n[ERROR] Por favor ingresa un numero valido.\n";
                continue;
            }
            cin.ignore(10000, '\n');

            if (opcion == 1) {
                cout << "Correo: "; cin >> buffer1;
                cout << "Contrasena: "; cin >> buffer2;
                if (iniciarSesion(Cadena(buffer1), Cadena(buffer2))) {
                    cout << "\n[OK] Sesion iniciada como " << usuarios[usuarioAutenticadoIndex].GETNombreUsuario().GETDatos() << endl;
                } else {
                    cout << "\n[ERROR] Credenciales incorrectas." << endl;
                }
            } else if (opcion == 2) {
                cout << "Nombre de Usuario: "; cin >> buffer1;
                cout << "Correo: "; cin >> buffer2;
                cout << "Contrasena: "; cin >> buffer3;
                Usuario nuevo(Cadena(buffer1), Cadena("01/01/2000"), Cadena(buffer2),
                              Cadena("default.jpg"), Cadena(buffer3), Cadena("Medellin"),
                              Cadena("Colombia"), Cadena("14/10/2026"));
                if (registrarUsuario(nuevo)) {
                    guardarDatos();
                    cout << "\n[OK] Usuario registrado exitosamente." << endl;
                } else {
                    cout << "\n[ERROR] El usuario o correo ya existe." << endl;
                }
            }
        } else {
            cout << " Usuario conectado: " << usuarios[usuarioAutenticadoIndex].GETNombreUsuario().GETDatos() << endl;
            cout << " 1. Enviar Mensaje" << endl;
            cout << " 2. Leer Nuevos Mensajes" << endl;
            cout << " 3. Enviar Solicitud de Amistad" << endl;
            cout << " 4. Aceptar Solicitud de Amistad" << endl;
            cout << " 5. Visitar Perfil de Amigo" << endl;
            cout << " 6. Cambiar Foto de Perfil (Alternar)" << endl;
            cout << " 7. Ver Reporte de Recursos (Medidor)" << endl;
            cout << " 8. Cerrar Sesion" << endl;
            cout << "Seleccione una opcion: ";

            int subOpcion;
            if (!(cin >> subOpcion)) {
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore(10000, '\n');


            if (subOpcion == 1) {
                cout << "Destinatario: ";
                cin >> buffer1;
                cout << "Mensaje: ";
                cin.ignore();
                cin.getline(buffer2, 256);
                enviarMensaje(Cadena(buffer1), Cadena(buffer2));
                guardarDatos();

            } else if (subOpcion == 2) {
                leerNuevosMensajes();
                guardarDatos();

            } else if (subOpcion == 3) {
                cout << "Usuario a solicitar: "; cin >> buffer1;
                enviarSolicitudAmistad(Cadena(buffer1));
                guardarDatos();

            } else if (subOpcion == 4) {
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
                    cin >> buffer1;
                    cin.ignore(10000, '\n');
                    aceptarSolicitudAmistad(Cadena(buffer1));
                    guardarDatos();
                }

            } else if (subOpcion == 5) {
                cout << "Nombre del amigo: "; cin >> buffer1;
                visitarPerfilAmigo(Cadena(buffer1));

            } else if (subOpcion == 6) {
                cambiarFotosPerfil();
                guardarDatos();

            } else if (subOpcion == 7){
                size_t heapTotal = 0;
                int totalU = matrizAmistades.getTotalUsuarios();

                if (totalU > 0) {
                    heapTotal += (totalU * totalU * sizeof(bool));
                }
                int numUsuarios = usuarios.GETTamanio();
                heapTotal += (numUsuarios * sizeof(Usuario));
                medidor.setMemoriaHeap(heapTotal);
                medidor.setMemoriaStack(sizeof(*this));
                medidor.reportarRecursos();

            } else if (subOpcion == 8) {
                usuarioAutenticadoIndex = -1;
                guardarDatos();
                cout << "\nSesion cerrada." << endl;
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