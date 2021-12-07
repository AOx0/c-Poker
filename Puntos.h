/*
 * @Crupier.h
 *
 * @brief Archivo de cabecera para lo definido en "Puntos.h".
 * Puntos representa el tipo de jugada que es una mano.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#ifndef POKER_PUNTOS_H
#define POKER_PUNTOS_H


typedef enum Puntos_ {
    EscaleraReal = 10,
    EscaleraDeColor = 9,
    Poquer = 8,
    Full = 7,
    Color = 6,
    Escalera = 5,
    Trio = 4,
    DoblePareja = 3,
    Pareja = 2,
    Jardin = 0
}Puntos;

void mostrarTipoMano(Puntos puntos);



#endif //POKER_PUNTOS_H
