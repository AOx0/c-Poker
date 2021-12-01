//
// Created by Alejandro D on 01/12/21.
//

#include <stdio.h>
#include "Crupier.h"
#include "Mano.h"


void juegaCrupier(Mesa * mesa, int mostrarInfo, int depht, Puntos puntosAnteriores, int changed[3]) {

    if (depht == 3) return;


    if (puntosAnteriores < calcularPuntos(&mesa->manoUno)) return;

    switch (mesa->manoUno.numCartasUtiles) {
        case 5:
            return;
        default:
            break;
    }

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


        return juegaCrupier(mesa, mostrarInfo, depht+1, mesa->manoUno.puntos, changed);
    }

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

            return juegaCrupier(mesa, mostrarInfo, depht+1, mesa->manoUno.puntos, changed);
        }
    }


}