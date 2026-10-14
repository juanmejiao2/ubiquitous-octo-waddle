#include <iostream>
#include "RedAmigos.h"
#include "medidorrecursos.h"

using namespace std;

int main() {
    cout << "=== PRUEBA DE INTEGRACION: REDAMIGOS + MEDIDORRECURSO ===" << endl << endl;

    // 1. Instanciar el medidor
    MedidorRecurso medidor;

    int numUsuarios = 5;
    // Tamaño exacto en Heap reservado por la matriz 1D (bool*)
    unsigned long long bytesRed = sizeof(bool) * numUsuarios * numUsuarios;

    // 2. Crear la red y registrar la reserva de memoria en el medidor
    cout << "[+] Creando RedAmigos para " << numUsuarios << " usuarios..." << endl;
    RedAmigos red(numUsuarios);
    medidor.registrarMemoriaHeap(bytesRed);

    // 3. Registrar amistades
    cout << "[+] Registrando relaciones de amistad..." << endl;

    // Usuario 0 es amigo de 1 y 2
    red.registrarAmistad(0, 1);
    medidor.registrarIteracion();

    red.registrarAmistad(0, 2);
    medidor.registrarIteracion();

    // Usuario 3 es amigo de 1 y 2
    red.registrarAmistad(3, 1);
    medidor.registrarIteracion();

    red.registrarAmistad(3, 2);
    medidor.registrarIteracion();

    // 4. Probar consultas de adyacencia
    cout << "\n--- CONSULTAS DE DOMINIO ---" << endl;
    cout << "¿Usuario 0 y Usuario 1 son amigos?: " << (red.sonAmigos(0, 1) ? "SI" : "NO") << endl;
    cout << "¿Usuario 0 y Usuario 3 son amigos?: " << (red.sonAmigos(0, 3) ? "SI" : "NO") << endl;

    // Conteo de amigos en común (recorre N elementos)
    int comunes = red.contarAmigosEnComun(0, 3);
    medidor.registrarIteracion(numUsuarios); // Auditoría: el algoritmo iteró N veces
    cout << "Amigos en comun entre Usuario 0 y 3 (esperado: 2): " << comunes << endl;

    // 5. Prueba de la Regla de los 3 (Copia profunda)
    cout << "\n[+] Probando copia profunda y destructor en bloque aislado..." << endl;
    {
        RedAmigos copiaRed = red; // Invoca constructor de copia
        medidor.registrarMemoriaHeap(bytesRed); // Se reservó un segundo bloque en Heap

        cout << "  -> Amigos en comun en la copia: " << copiaRed.contarAmigosEnComun(0, 3) << endl;

        // Al cerrar este bloque {}, copiaRed se destruye automáticamente
        medidor.liberarMemoriaHeap(bytesRed);
        cout << "  -> Copia destruida y memoria descontada del medidor." << endl;
    }

    // 6. Ver reporte de métricas acumuladas
    medidor.reportarRecursos();

    // 7. Simular la liberación final
    medidor.liberarMemoriaHeap(bytesRed);
    cout << "Memoria Heap remanente al finalizar: " << medidor.getMemoriaHeap() << " bytes." << endl;
    cout << "\n=== PRUEBA COMPLETADA EXITOSAMENTE ===" << endl;

    return 0;
}