/*
 * @Crupier.h
 *
 * @brief Archivo de cabecera para lo definido en "Mano.h".
 *
 * @author AOx0
 * @date 30/11/2021
 */

#define bool int

#ifndef POKER_MANO_H
#define POKER_MANO_H

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
bool containsValue(Mano mano, Valor valor);
bool containsValues(Mano mano, Valor valores[5]);

Puntos calcularPuntos(Mano * mano);
void calcularYActualizarPuntos(Mano * mano);


#endif //POKER_MANO_H
