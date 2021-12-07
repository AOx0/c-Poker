/*
* @Cartas.c
*
* @brief Archivo con la definición de métodos relacionados a la estructura Carta y a los enums que la conforman.
*
* @author AOx0
* @date 30/11/2021
*/

#include <stdio.h>
#include "Carta.h"


void imprimirCarta(Carta carta) {
    const char *figura[ 4 ] = { "Corazones", "Diamantes", "Treboles", "Espadas" };
    const char *valor[ 13 ] = { "As", "Dos", "Tres", "Cuatro", "Cinco", "Seis", "Siete", "Ocho",
                          "Nueve", "Diez", "Jota", "Reina", "Rey" };
    printf("%8s de %s (%d)\n", valor[(int)carta.valor], figura[(int)carta.figura], carta.valor);
}

