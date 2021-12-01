cmake_minimum_required(VERSION 3.20)
project(poker C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(poker
        main.c Carta.c Carta.h Mano.c Mano.h Mesa.c Mesa.h Puntos.c Puntos.h Crupier.c Crupier.h)
