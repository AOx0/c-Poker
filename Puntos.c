//
// Created by Alejandro D on 30/11/21.
//

#include <libc.h>
#include "Puntos.h"


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
