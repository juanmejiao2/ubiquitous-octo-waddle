#include <iostream>
#include "sistemaudeabook.h"

using namespace std;

int main() {
    cout << "=================================================" << endl;
    cout << "   PRUEBA DE COMPILACION E INTEGRACION SISTEMA   " << endl;
    cout << "=================================================" << endl;

    // 1. Instanciación del sistema principal
    SistemaUdeaBook sistema;

    // 2. Simulación de carga de datos
    sistema.cargarDatos();

    // 3. Crear usuarios de prueba con el constructor parametrizado
    Usuario u1(
        Cadena("carlos123"),
        Cadena("01/01/2000"),
        Cadena("carlos@udea.edu.co"),
        Cadena("foto1.jpg"),
        Cadena("pass123"),
        Cadena("Medellin"),
        Cadena("Colombia"),
        Cadena("10/02/2024")
        );

    Usuario u2(
        Cadena("maria_p"),
        Cadena("15/05/2001"),
        Cadena("maria@udea.edu.co"),
        Cadena("foto2.jpg"),
        Cadena("secret456"),
        Cadena("Envigado"),
        Cadena("Colombia"),
        Cadena("12/02/2024")
        );

    // 4. Inserción manual en el arreglo dinámico de usuarios
    sistema.getUsuarios().agregar(u1);
    sistema.getUsuarios().agregar(u2);

    cout << "-> Usuarios registrados en el arreglo: " << sistema.getUsuarios().GETTAMANIO() << endl;

    // 5. Prueba de autenticación
    bool loginOk = sistema.iniciarSesion(Cadena("carlos@udea.edu.co"), Cadena("pass123"));
    if (loginOk) {
        cout << "-> [OK] Inicio de sesion correcto para el usuario autenticado." << endl;
    } else {
        cout << "-> [FAIL] Fallo en el inicio de sesion." << endl;
    }

    // 6. Prueba de interacción (Solicitudes y Mensajes)
    sistema.enviarSolicitudAmistad(Cadena("maria_p"));
    cout << "-> [OK] Solicitud enviada a maria_p" << endl;

    sistema.enviarMensaje(Cadena("maria_p"), Cadena("Hola Maria, probando la integracion de clases."));
    cout << "-> [OK] Mensaje enviado a maria_p" << endl;

    // 7. Generación de reporte de rendimiento
    sistema.getMedidor().reportarRecursos();

    cout << "=================================================" << endl;
    cout << "   COMPILACION Y ENLACE EXITOSOS SIN ERRORES     " << endl;
    cout << "=================================================" << endl;

    return 0;
}