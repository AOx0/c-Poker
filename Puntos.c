/*
 * @Puntos.c
 *
 * @brief Archivo de código fuente para los prototipos definidos en "Puntos.h".
 *
 * Define la estructura Puntos por separado para no extender de más Mano. Puntos representa el tipo de jugada que es una
 * mano. El único método útil es mostrar la jugada como string.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#include <string.h>
#include <stdio.h>
#include "Puntos.h"

/*
 * Función que muestra el tipo de jugada de acuerdo a su posición. Para hacer el código mas leible se usó el enum
 * Puntos.
 *
 * @param puntos El valor de la jugada de la mano
 */
void mostrarTipoMano(Puntos puntos) {
    char resultado[100];
    switch (puntos) {
        case EscaleraReal: strcpy(resultado, "Escalada Real"); break;
        case EscaleraDeColor: strcpy(resultado, "Escalada De Color"); break;
        case Poquer: strcpy(resultado, "Póquer"); break;
        case Full: strcpy(resultado, "Full"); break;
        case Color: strcpy(resultado, "Color"); break;
        case Escalera: strcpy(resultado, "Escalera"); break;
        case Trio: strcpy(resultado, "Trio"); break;
        case DoblePareja: strcpy(resultado, "Doble Par"); break;
        case Pareja: strcpy(resultado, "Par"); break;
        case Jardin: strcpy(resultado, "Jardín"); break;
    }

    printf("El tipo de mano es: %s (Puntos: %d)\n", resultado, (int)puntos);
}
