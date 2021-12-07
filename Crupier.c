/*
 * @Crupier.c
 *
 * @brief Archivo de código fuente para los prototipos definidos en "Crupier.h".
 *
 * Este archivo contiene el procedimiento que realiza el Crupier para jugar por si mismo, analizando su mano y tomando
 * acción dependiendo de la misma.
 *
 * Si su mano es buena, es decir, si no puede cambiar ni una de las cartas para no afectar la jugada, no toma acción.
 * Siempre elige qué carta cambiar sin afectar las que conforman la jugada principal, no se arriesga.
 * Primero cambiará las cartas con menos valor, para intentar obtener una mayor y ganar en caso de empate.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#include <stdio.h>
#include "Crupier.h"
#include "Mano.h"

/*
 * Procedimiento para que el Crupier juegue. Es recursiva, ejecutándose hasta 3 veces para hacer los 3 cambios de carta
 * permitidos por las especificaciones del profesor.
 *
 * @param mesa Apuntador a la mesa de juego, usado para poder cambiar cartas por las de la baraja
 * @param mostrarInfo Booleano que indica si se debe imprimir información sensible como las cartas que tiene el crupier,
 * qué cambios realizó, que dió, qué obtuvo, etc.
 * @param depht Int que debe valer 0 siempre que se ejecute por primera vez, indica el número de cambios de carta
 * realizados
 * @param puntosAnteriores Integer que almacena la cantidad de puntos logrados por el crupier antes de hacer un cambio
 * de carta. En cuanto logra aumentar los puntos deja de cambiar cartas.
 * @param changed Lista que contiene los índices de las cartas ya cambiadas por el Crupier
 */
void juegaCrupier_(Mesa * mesa, int mostrarInfo, int depht, Puntos puntosAnteriores, int changed[3]) {

    // Si ya cambió 3 cartas se termina la recursividad.
    if (depht == 3) return;

    // Si junta más puntos que los que tenía antes, termina de cambair cartas
    if (puntosAnteriores < calcularPuntos(&mesa->manoUno)) return;

    // Si es una jugada ideal, se da por servido.
    switch (mesa->manoUno.numCartasUtiles) {
        case 5:
            return;
        default:
            break;
    }

    // Primero se deshace de las cartas más pequeña
    if (!arrayContainsValue(mesa->manoUno.i_masBaja, 3, changed) && !arrayContainsValue(mesa->manoUno.i_masBaja, 5, mesa->manoUno.i_cartasUtiles) ) {

        if (mostrarInfo) {
            printf("El Crupier cambiará su carta (más baja) %d\nLa carta es: \n", mesa->manoUno.i_masBaja+1);
            imprimirCarta(*mesa->manoUno.cartas[mesa->manoUno.i_masBaja]);
        } else {
            printf("El Crupier cambiará su carta %d\n", mesa->manoUno.i_masBaja+1);
        }

        cambiarCarta(mesa, JugadorUno, mesa->manoUno.i_masBaja);
        changed[depht] = mesa->manoUno.i_masBaja;

        if (mostrarInfo) {
            printf("La carta que obtuvo es: \n");
            imprimirCarta(*mesa->manoUno.cartas[mesa->manoUno.i_masBaja]);
        }


        return juegaCrupier_(mesa, mostrarInfo, depht+1, mesa->manoUno.puntos, changed);
    }

    // Después se deshace de cualquier otra carta
    for (int j=0; j<5; j++) {
        if (arrayContainsValue(j, 5, mesa->manoUno.i_cartasUtiles) || arrayContainsValue(j, 3, changed)) continue;
        else {
            if (mostrarInfo) {
                printf("El Crupier cambiará su carta %d\nLa carta es: \n", j + 1);
                imprimirCarta(*mesa->manoUno.cartas[j]);
            } else {
                printf("El Crupier cambiará su carta %d\n", j + 1);
            }

            cambiarCarta(mesa, JugadorUno, j);
            changed[depht] = j;

            if (mostrarInfo) {
                printf("La carta que obtuvo es: \n");
                imprimirCarta(*mesa->manoUno.cartas[j]);
            }

            return juegaCrupier_(mesa, mostrarInfo, depht+1, mesa->manoUno.puntos, changed);
        }
    }


}

/*
 * Interfaz de juegaCrupier_.
 * Solo es necesario obtener la mesa y si se muestra o no la info al usuario, los demás datos son siempre los mismos,
 * por lo que no es necesario hacer que el "frontend" sepa o se preocupe.
 * @param mesa Mesa del juego al que pertenece el Crupier
 * @param mostrarInfo Si se debe o no mostrar información sobre los cambios de carta y baraja del Crupier
 */
void juegaCrupier(Mesa * mesa, int mostrarInfo) {
    int changedValues[3] = {-1, -1,-1};
    return juegaCrupier_(mesa, mostrarInfo, 0, mesa->manoUno.puntos, changedValues);
}