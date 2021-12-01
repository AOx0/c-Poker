/*
* @main.c
*
* @brief Archivo principal del directorio, contiene la lógica que sigue el programa. El programa es capaz de ofrecer a un
* jugador jugar Poker y evaluar su mano.
*
* @author Pedro Terán
* @date 30/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Carta.h"
#include "Mano.h"
#include "Mesa.h"

void shuffle( int [4][ 13 ] );
void reparte( int [4][ 13 ],  Carta [4 * 13]  );

void evaluaUnaMano(Mano mano) {
    mostrarTipoMano(mano.puntos);
}

void evaluaDosManos(Carta deck[13*4], Mano mano1, Mano mano2) {
    Mesa mesa = crearMesa(deck, mano1, mano2);

    determinarGanador(&mesa);
    mostrarGanador(&mesa);
}

void evaluarMesa(Mesa * mesa) {
    determinarGanador(mesa);
    mostrarGanador(mesa);
}

int main( void ) {


    while (1) {

        int opcion;

        int deck[ 4 ][ 13 ] = { 0 };
        Carta cartas[13 * 4];
        Mesa mesa;

        Mano manoUno, manoDos;

        srand( time( 0 ) );

        shuffle( deck );
        reparte( deck, cartas );

        Carta parte1[5] = {cartas[51],cartas[50],cartas[49],cartas[48],cartas[47] };
        Carta parte2[5] = {cartas[46],cartas[45],cartas[44],cartas[43],cartas[42] };

        manoUno = crearMano(parte1);
        manoDos = crearMano(parte2);

        mesa = crearMesa(cartas, manoUno, manoDos);




        printf(
                "Menú\n"
                "1.Evalúa una mano\n"
                "2.Evalúa dos manos\n"
                "3.El crupier juega\n"
                "4.Un juego vs el crupier\n"
                "5.Fin\n"
        );
        printf("Elige tu opción: ");




        scanf(" %d", &opcion);

        if (opcion == 5) break;

        switch (opcion) {
            case 1:
                puts("Evaluando la mano:");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(mesa.manoUno);
                break;
            case 2:
                puts("Evaluando como mano 1:");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(mesa.manoUno);

                puts("Evaluando como mano 2:");
                mostrarMano(mesa.manoDos);
                evaluaUnaMano(mesa.manoDos);
                evaluaDosManos(cartas, mesa.manoUno, mesa.manoDos);
                break;
        }

        printf("\n");
    }




    return 0;
 
}

 void shuffle( int Deck[4][ 13 ] ) {
 int fila;
 int columna;
 int carta;

     for ( carta = 1; carta <= 52; carta++){

       do{
           fila = rand() % 4;
           columna = rand() % 13;
       } while( Deck[ fila ][ columna ] != 0 );

     Deck[ fila ][ columna ] = carta;
     }
 }
    
 void reparte( int Deck[4][ 13 ], Carta cartas[4 * 13] )
 {

     int carta;
     int fila;
     int columna;

     for ( carta = 1; carta <= 52; carta++ ) {
         for ( fila = 0; fila <= 3; fila++ ) {
             for ( columna = 0; columna <= 12; columna++ ) {
                 if ( Deck[ fila ][ columna ] == carta ) {
                     Carta c = { fila, columna };
                     cartas[carta] = c;
                 }
             }
         }
     }

}
