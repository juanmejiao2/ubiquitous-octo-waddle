#include "sistemaudeabook.h"

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
    if (!archivo.is_open()) return;

    char bufferTipo[64];
    while (archivo >> bufferTipo) {
        medidor.registrarIteracion();
        Cadena tipo(bufferTipo);

        if (tipo == Cadena("[USUARIOS]")) {
            int cantidad = 0;
            archivo >> cantidad;
            archivo.get(); // Consumir salto de línea
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
        }
    }
    archivo.close();
}


void SistemaUdeaBook::guardarDatos() {
    medidor.registrarIteracion();
    ofstream archivo("datos.txt");
    if (!archivo.is_open()) return;

    int totalUsuarios = usuarios.GETTAMANIO();
    archivo << "[USUARIOS]\n" << totalUsuarios << "\n";
    for (int i = 0; i < totalUsuarios; ++i) {
        medidor.registrarIteracion();
        archivo << usuarios[i].NombreUsuario.GETDatos() << ";"
                << usuarios[i].FechaNacimiento.GETDatos() << ";"
                << usuarios[i].Correo.GETDatos() << ";"
                << usuarios[i].FotoPerfil.GETDatos() << ";"
                << usuarios[i].Contrasena.GETDatos() << ";"
                << usuarios[i].Ciudad.GETDatos() << ";"
                << usuarios[i].Pais.GETDatos() << ";"
                << usuarios[i].FechaInscripcion.GETDatos() << "\n";
    }
    archivo.close();
}

bool SistemaUdeaBook::iniciarSesion(Cadena correo, Cadena contrasena) {
    medidor.registrarIteracion();
    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].correo == correo && usuarios[i].validarContrasenia(contrasena)) {
            usuarioAutenticadoIndex = i;
            return true;
        }
    }
    return false;
}

bool SistemaUdeaBook::registrarUsuario(const Usuario& nuevoUsuario) {
    medidor.registrarIteracion();
    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].NombreUsuario() == nuevoUsuario.NombreUsuario() ||
            usuarios[i].Correo == nuevoUsuario.correo) {
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

    Cadena emisor = usuarios[usuarioAutenticadoIndex].NombreUsuario;
    SolicitudAmistad sol(emisor, receptor);

    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].NombreUsuario == receptor) {
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

        ArregloDinamico<SolicitudAmistad>& solRecibidas = usuarios[usuarioAutenticadoIndex].solicitudes;
    int total = solRecibidas.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (solRecibidas[i].GETEmisor() == emisor && solRecibidas[i].GETEstado() == Cadena("Pendiente")) {
            solRecibidas[i].cambiarEstado(Cadena("Aceptada"));
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
    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == nombreAmigo) {
            cout << "\n=== PERFIL DE " << nombreAmigo.GETDatos() << " ===" << endl;
            cout << "Ciudad: " << usuarios[i].ciudad.GETDatos() << endl;
            cout << "Pais: " << usuarios[i].pais.GETDatos() << endl;
            return;
        }
    }
    cout << "El usuario no existe." << endl;
}

void SistemaUdeaBook::enviarMensaje(Cadena receptor, Cadena contenido) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].NombreUsuario;
    Mensaje msj(emisor, receptor, contenido, Cadena("Sin fecha"));

    int total = usuarios.GETTAMANIO();
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

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].mensajesRecibidos;
    int total = recibidos.GETTAMANIO();
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
    if (!hayNuevos) cout <<"no tienes mensajes nuevos. "endl;
}

void SistemaUdeaBook::buscarMensajesPorFecha(Cadena fecha, Cadena emisor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].mensajesRecibidos;
    int total = recibidos.GETTAMANIO();
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
            cin >> opcion;

            if (opcion == 1) {
                cout << "Correo: "; cin >> buffer1;
                cout << "Contrasena: "; cin >> buffer2;
                if (iniciarSesion(Cadena(buffer1), Cadena(buffer2))) {
                    cout << "\n[OK] Sesion iniciada como " << usuarios[usuarioAutenticadoIndex].NombreUsuario.GETDatos() << endl;
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
                    cout << "\n[OK] Usuario registrado exitosamente." << endl;
                } else {
                    cout << "\n[ERROR] El usuario o correo ya existe." << endl;
                }
            }
        } else {
            cout << " Usuario conectado: " << usuarios[usuarioAutenticadoIndex].NombreUsuario.GETDatos() << endl;
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
            cin >> subOpcion;

            if (subOpcion == 1) {
                cout << "Destinatario: "; cin >> buffer1;
                cout << "Mensaje: "; cin.ignore(); cin.getline(buffer2, 256);
                enviarMensaje(Cadena(buffer1), Cadena(buffer2));
            } else if (subOpcion == 2) {
                leerNuevosMensajes();
            } else if (subOpcion == 3) {
                cout << "Usuario a solicitar: "; cin >> buffer1;
                enviarSolicitudAmistad(Cadena(buffer1));
            } else if (subOpcion == 4) {
                cout << "Usuario que te envio solicitud: "; cin >> buffer1;
                aceptarSolicitudAmistad(Cadena(buffer1));
            } else if (subOpcion == 5) {
                cout << "Nombre del amigo: "; cin >> buffer1;
                visitarPerfilAmigo(Cadena(buffer1));
            } else if (subOpcion == 6) {
                cambiarFotosPerfil();
            } else if (subOpcion == 7) {
                medidor.reportarRecursos();
            } else if (subOpcion == 8) {
                usuarioAutenticadoIndex = -1;
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