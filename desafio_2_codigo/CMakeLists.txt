cmake_minimum_required(VERSION 3.16)

project(desafio_2_codigo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(desafio_2_codigo main.cpp
    cadena.h cadena.cpp
    arreglodinamico.h
    foto.h foto.cpp
    album.h album.cpp
    mensaje.h mensaje.cpp
    solicitudamistad.h solicitudamistad.cpp
    usuario.h usuario.cpp
    album.h arreglodinamico.h medidorrecursos.h redamigos.h sistemaudeabook.h mensaje.h solicitudamistad.h foto.h cadena.h
    album.cpp main.cpp medidorrecursos.cpp sistemaudeabook.cpp usuario.cpp mensaje.cpp redamigos.cpp solicitudamistad.cpp foto.cpp cadena.cpp)

include(GNUInstallDirs)
install(TARGETS desafio_2_codigo
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/datos.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})