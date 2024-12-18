cmake_minimum_required(VERSION 3.26)
project(TP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TP main.cpp
        caravana.h
        grelha.h
        item.h
        jogador.h
        combate.h
        caravana.cpp
        combate.cpp
        grelha.cpp
        item.cpp
        jogador.cpp
        UI.h
        UI.cpp)
