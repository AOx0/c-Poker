/*
* @Cartas.h
*
* @brief Archivo con la definición de métodos relacionados y de la estructura Carta y a los enums que la conforman.
*
* @author Pedro Terán
* @date 30/11/2021
*/

#ifndef PEDRO_CARTA_H
#define PEDRO_CARTA_H

typedef enum Figura_ {
    Corazones = 1,
    Diamantes = 2,
    Treboles = 4,
    Espadas = 5
}Figura;

typedef enum Valor_ {
    As = 14,
    Dos = 2,
    Tres = 3,
    Cuatro = 4,
    Cinco = 5,
    Seis = 6,
    Siete = 7,
    Ocho = 8,
    Nueve = 9,
    Diez = 10,
    Jota = 11,
    Reina = 12,
    Rey = 13
}Valor;

typedef struct Carta_ {
    Figura figura;
    Valor valor;

}Carta;

void imprimirCarta(Carta carta);

#endif //PEDRO_CARTA_H
