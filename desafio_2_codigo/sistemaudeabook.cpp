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


void SistemaUdeaBook::cargarDatos() {
    medidor.registrarIteracion();
}

void SistemaUdeaBook::guardarDatos() {
    medidor.registrarIteracion();
}

bool SistemaUdeaBook::iniciarSesion(Cadena correo, Cadena contrasena) {
    medidor.registrarIteracion();
    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].validarContrasenia(contrasena)) {
            usuarioAutenticadoIndex = i;
            return true;
        }
    }
    return false;
}

void SistemaUdeaBook::mostrarMejoresAmigos() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
}

void SistemaUdeaBook::cambiarFotosPerfil() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
    yaAlternoFotos = !yaAlternoFotos;
}

void SistemaUdeaBook::enviarSolicitudAmistad(Cadena receptor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();
    SolicitudAmistad sol(emisor, receptor);

    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
            usuarios[i].recibirSolicitud(sol);
            break;
        }
    }
}

void SistemaUdeaBook::aceptarSolicitudAmistad(Cadena emisor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;
}

void SistemaUdeaBook::verSugerenciasAmistad(int idUsuario) {
    medidor.registrarIteracion();
}

void SistemaUdeaBook::visitarPerfilAmigo(Cadena nombreAmigo) {
    medidor.registrarIteracion();
}

void SistemaUdeaBook::enviarMensaje(Cadena receptor, Cadena contenido) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    Cadena emisor = usuarios[usuarioAutenticadoIndex].GETNombreUsuario();
    Mensaje msj(emisor, receptor, contenido, Cadena("Sin fecha"));

    int total = usuarios.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (usuarios[i].GETNombreUsuario() == receptor) {
            usuarios[i].recibirMensaje(msj);
            break;
        }
    }
}

void SistemaUdeaBook::leerNuevosMensajes() {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].GETMensajesRecibidos();
    int total = recibidos.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (!recibidos[i].esLeido()) {
            recibidos[i].marcarLeido();
        }
    }
}

void SistemaUdeaBook::buscarMensajesPorFecha(Cadena fecha, Cadena emisor) {
    medidor.registrarIteracion();
    if (usuarioAutenticadoIndex == -1) return;

    ArregloDinamico<Mensaje>& recibidos = usuarios[usuarioAutenticadoIndex].GETMensajesRecibidos();
    int total = recibidos.GETTAMANIO();
    for (int i = 0; i < total; ++i) {
        medidor.registrarIteracion();
        if (recibidos[i].GETfecha() == fecha && recibidos[i].GETEmisor() == emisor) {
            // Coincidencia encontrada
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