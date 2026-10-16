#include "sistemaudeabook.h"

int main() {
    SistemaUdeaBook sistema;
    sistema.cargarDatos();
    sistema.ejecutarMenu();
    sistema.guardarDatos();
    return 0;
}