#include "sistemaudeabook.h"

int main() {
    SistemaUdeaBook sistema;
    sistema.cargarDatos();   // 1. Carga los datos del .txt
    sistema.ejecutarMenu();  // 2. Ejecuta todo el flujo interactivo
    sistema.guardarDatos();  // 3. Guarda los cambios de vuelta en el .txt
    return 0;
}