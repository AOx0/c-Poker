//
// Created by Alejandro D on 30/11/21.
//

#include "Mano.h"

#ifndef PEDRO_MESA_H
#define PEDRO_MESA_H

typedef enum Jugador_ {
    JugadorUno,
    JugadorDos,
    None
}Jugador;

typedef struct Mesa_ {
    Carta  deck[13 * 4];
    int deckIndex;
    Mano manoUno;
    Mano manoDos;
    Jugador ganador;
}Mesa;

Jugador determinarGanador_(Mesa* mesa);
void determinarGanador(Mesa* mesa);
void mostrarGanador(Mesa *mesa);
Mesa crearMesa(Carta deck[13 * 4], Mano mano1, Mano mano2);
void cambiarCarta(Mesa * mesa, Jugador jugador, int i);


#endif //PEDRO_MESA_H
