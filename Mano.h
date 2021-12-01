//
// Created by Alejandro D on 29/11/21.
//

#define bool int

#ifndef PEDRO_MANO_H
#define PEDRO_MANO_H

#include "Carta.h"
#include "Puntos.h"

typedef struct Mano_ {
    Carta * cartas[5];
    int sonMismaFigura;
    Carta masAlta;
    int i_masAlta;
    Carta masBaja;
    int i_masBaja;
    Puntos puntos;
    int i_cartasUtiles[5];
    int numCartasUtiles;
} Mano;

Mano crearMano(Carta cartas[5]);
void mostrarMano(Mano mano);

bool esEscaleraReal(Mano * mano);
bool esEscaleraDeColor(Mano * mano);
bool esPoquer(Mano * mano);
bool esFull(Mano * mano);
bool esColor(Mano * mano);
bool esEscalera(Mano * mano);
bool esTrio(Mano * mano);
bool esDoblePareja(Mano * mano);
bool esPareja(Mano * mano);
Carta esMasAlta(Mano * mano);

bool arrayContainsValue(int valor, int size, const int array[size] );
bool containsValue(Mano mano, Valor valor, int exceptSize,  int exceptArray[exceptSize]);
bool containsValues(Mano mano,  int valoresSize, Valor valores[valoresSize], int exceptSize,  int exceptArray[exceptSize]);

Puntos calcularPuntos(Mano * mano);
void calcularYActualizarPuntos(Mano * mano);


#endif //PEDRO_MANO_H
