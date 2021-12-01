//
// Created by Alejandro D on 30/11/21.
//
#include <stdio.h>
#include <libc.h>
#include "Mesa.h"

Jugador determinarGanador_(Mesa *mesa) {

    if ((int)mesa->manoUno.puntos > (int)mesa->manoDos.puntos) return JugadorUno;
    if ((int)mesa->manoUno.puntos < (int)mesa->manoDos.puntos) return JugadorDos;

    if ((int)mesa->manoUno.masAlta.valor > (int)mesa->manoDos.masAlta.valor) return JugadorUno;
    if ((int)mesa->manoUno.masAlta.valor < (int)mesa->manoDos.masAlta.valor) return JugadorDos;


    return None;
}

void determinarGanador(Mesa  * mesa) {
    mesa->ganador = determinarGanador_(mesa);
}

void mostrarGanador(Mesa *mesa) {

    printf("La mano ganadora es "
        "%s\n", mesa->ganador == JugadorUno ? "la 1 (Crupier)" :  mesa->ganador == JugadorDos ? "la 2 (Tu)" : "Empate"
    );
}

void cambiarCarta(Mesa * mesa, Jugador jugador, int i) {
    if (jugador == JugadorUno) mesa->manoUno.cartas[i] = &mesa->deck[mesa->deckIndex];
    else mesa->manoDos.cartas[i] = (Carta *) &mesa->deck[mesa->deckIndex];

    mesa->deckIndex-=1;
}

Mesa crearMesa(Carta   deck[13 * 4], Mano mano1, Mano mano2) {
    Mesa mesa = {
            .deck =  0,
            .manoUno = mano1,
            .manoDos = mano2,
            .ganador = None,
            .deckIndex = 41
    };

    memcpy(mesa.deck, deck, (13*4)*(sizeof (Carta)));

    return mesa;
}