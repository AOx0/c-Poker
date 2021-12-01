//
// Created by Alejandro D on 30/11/21.
//
#include <stdio.h>
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

    printf("El ganador es: "
        "%s\n", mesa->ganador == JugadorUno ? "El jugador 1" :  mesa->ganador == JugadorDos ? "El jugador 2" : "Empate"
    );
}

void cambiarCarta(Mesa * mesa, Jugador jugador, int i) {
    if (jugador == JugadorUno) mesa->manoUno.cartas[i] = (Carta *) &mesa->deck[mesa->deckIndex];
    else mesa->manoDos.cartas[i] = (Carta *) &mesa->deck[mesa->deckIndex];
    mesa->deckIndex--;
}

Mesa crearMesa(Carta deck[13 * 4], Mano mano1, Mano mano2) {
    Mesa mesa = {
            .deck =  deck,
            .manoUno = mano1,
            .manoDos = mano2,
            .ganador = None,
            .deckIndex = 41
    };
    return mesa;
}