//
// Created by Alejandro D on 29/11/21.
//

#ifndef PEDRO_MANO_H
#define PEDRO_MANO_H

#include "Carta.h"
#include "Puntos.h"

typedef struct Mano_ {
    Carta * cartas[5];
    int sonMismaFigura;
    Carta masAlta;
    int i_masAlta;
    Puntos puntos;
    int i_cartasUtiles[5];
} Mano;

Mano crearMano(Carta cartas[5]);
void mostrarMano(Mano mano);

int esEscaleraReal(Mano * mano);
int esEscaleraDeColor(Mano * mano);
int esPoquer(Mano * mano);
int esFull(Mano * mano);
int esColor(Mano * mano);
int esEscalera(Mano * mano);
int esTrio(Mano * mano);
int esDoblePareja(Mano * mano);
int esPareja(Mano * mano);
Carta esMasAlta(Mano * mano);


#endif //PEDRO_MANO_H
