//
// Created by Alejandro D on 30/11/21.
//



#ifndef PEDRO_PUNTOS_H
#define PEDRO_PUNTOS_H


typedef enum Puntos_ {
    EscaleraReal = 10,
    EscaleraDeColor = 9,
    Poquer = 8,
    Full = 7,
    Color = 6,
    Escalera = 5,
    Trio = 4,
    DoblePareja = 3,
    Pareja = 2,
    Jardin = 0
}Puntos;

void mostrarTipoMano(Puntos puntos);



#endif //PEDRO_PUNTOS_H
