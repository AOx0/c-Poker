/*
 * @main.c
 *
 * @brief Archivo principal del directorio, contiene la lógica que sigue el programa. El programa es capaz de ofrecer a un
 * jugador jugar Poker contra la computadora, evaluar una mano generada aleatoriamente, evaluar dos manos generadas
 * aleatoriamente.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "Carta.h"
#include "Mano.h"
#include "Mesa.h"
#include "Crupier.h"

void shuffle( int [4][ 13 ] );
void reparte( int [4][ 13 ],  Carta [4 * 13]  );

int main( int argc, char **argv );
void evaluaUnaMano(Mano * mano);
void evaluarMesa(Mesa * mesa);

/*
 * Procedimiento que evalúa una mano y muestra el tipo de jugada que es.
 * @param mano Apuntador a una instancia de Mano
 */
void evaluaUnaMano(Mano * mano) {
    calcularYActualizarPuntos(mano);
    mostrarTipoMano(mano->puntos);
}

/*
 * Procedimiento que evalúa una mano y muestra el tipo de jugada que es.
 * @param mano Apuntador a una instancia de Mano
 */
void evaluarMesa(Mesa * mesa) {
    determinarGanador(mesa);
    mostrarGanador(mesa);
}

/*
 * Procedimiento que evalúa dos manos, usándolas para crear una mesa y muestra el tipo de jugada que son además de
 * cuál de las dos es la ganadora.
 * @param deck Arreglo de 52 Cartas que representa la pila de cartas ya barajadas
 * @param mano1 Instancia de mano con las cartas de la mano 1
 * @param mano2 Instancia de mano con las cartas de la mano 2
 */
void evaluaDosManos(Carta deck[13*4], Mano mano1, Mano mano2) {
    Mesa mesa = crearMesa(deck, mano1, mano2);

    evaluarMesa(&mesa);
}

/*
* Procedimiento que limpia la pantalla
*/
void clearScreen() {
    system("clear");
}

/*
 * Procedimiento que pide un caracter antes de seguir con la ejecución del programa
 */
void pressToContinue() {

    char misc[50];

    printf("Ingresa cualquier carácter para continuar: ");
    scanf("%s", misc);
}

/*
 * Función principal.
 *      En caso de recibir -a muestra los resultados de jugar 20 partidas contra el Crupier
 *      En caso de recibir -c muestra los cambios realizados a la "IA" del Crupier
 *
 * @param argc Integer con el número de argumentos pasados al ejecutar el programa
 * @param argv Lista de argumentos pasados al ejecutar el programa
 * @return Devuelve el estado de salida del programa. Un 0 es correcto
 */
int main( int argc, char **argv ) {

    if (argc != 1) {
        if (strcmp(argv[1], "-a") == 0)
            printf("Los 20 juegos fueron: \n"
                   "N   Crupier|Jugador            Ganador\n\n"
                   "1.  0 -> 2 & 0 -> 2         -- Crupier\n"
                   "2.  0 -> 2 & 0 -> 0         -- Crupier\n"
                   "3.  2 -> 2 & 0 -> 0         -- Crupier\n"
                   "4.  2 -> 2 & 0 -> 2         -- Jugador\n"
                   "5.  6 -> 6 & 3 -> 3         -- Crupier\n"
                   "6.  2 -> 2 & 0 -> 0         -- Crupier\n"
                   "7.  2 -> 4 & 0 -> 2         -- Crupier\n"
                   "8.  2 -> 3 & 3 -> 3         -- Crupier\n"
                   "9.  5 -> 5 & 6 -> 6         -- Jugador\n"
                   "10. 2 -> 2 & 0 -> 0         -- Crupier\n"
                   "11. 0 -> 2 & 0 -> 2         -- Jugador\n"
                   "12. 2 -> 2 & 2 -> 2         -- Jugador\n"
                   "13. 3 -> 3 & 0 -> 2 -> 0    -- Crupier\n"
                   "14. 2 -> 2 & 0 -> 2         -- Crupier\n"
                   "15. 0 -> 2 & 3 -> 3         -- Jugador\n"
                   "16. 2 -> 4 & 2 -> 3         -- Crupier\n"
                   "17. 2 -> 3 & 2 -> 2         -- Crupier\n"
                   "18. 2 -> 2 & 2 -> 2         -- Crupier\n"
                   "19. 2 -> 2 & 2 -> 2         -- Jugador\n"
                   "20. 0 -> 2 & 2 -> 2         -- Crupier\n"
                   "\n"
                   "Promedio de mejora del Crupier: 0.7\n"
                   "Promedio de mejora del Jugador: 0.55\n"
                   "\n"
                   "Victorias Crupier: 14\n"
                   "Victorias Jugador: 6\n"
                   "\n"
                   "Es clara la superioridad del Crupier en mejora de jugada.\n"
                   "Es importante mencionar que el Crupier nada sabe sobre la\n"
                   "próxima carta que saldrá en el Deck de cartas ni sabe nada\n"
                   "sobre las cartas del jugador, es simple suerte y \"habilidad\".\n");
        if (strcmp(argv[1], "-c") == 0)
            printf(
                    "Los cambios fueron nulos, el Crupier mostró ser competente\n"
                    "desde la primera versión de su algoritmo.\n"
                    "Si tiene una jugada donde las 5 cartas que tiene se usan,\n"
                    "entonces no realiza una acción y se da por servido.\n"
                    "\n"
                    "Si tiene una mala jugada, primero se deshace de las cartas\n"
                    "más bajas de su mano. Cada que cambia una carta evalúa su\n"
                    "puntuación y revisa cuál es su carta más baja para elegir.\n"
            );
        puts(" ");
        return 0;
    }

    clearScreen();

    puts(
        "Desarrollado por:\n"
        "    - AOx0\n"
    );

    pressToContinue();
    clearScreen();


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
                clearScreen();
                puts("Evaluando la mano:");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(&mesa.manoUno);

                pressToContinue();
                clearScreen();
                break;
            case 2:
                clearScreen();
                puts("Evaluando la mano del Crupier:");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(&mesa.manoUno);

                puts(" ");

                puts("Evaluando como mano del \"Jugador\":");
                mostrarMano(mesa.manoDos);
                evaluaUnaMano(&mesa.manoDos);
                evaluaDosManos(cartas, mesa.manoUno, mesa.manoDos);

                puts(" ");

                pressToContinue();
                clearScreen();
                break;
            case 3:
                clearScreen();
                puts("El Crupier tiene: ");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(&mesa.manoUno);


                puts(" ");

                juegaCrupier(&mesa, 1);

                puts(" ");

                puts("El Crupier terminó con: ");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(&mesa.manoUno);

                pressToContinue();
                clearScreen();
                break;
            case 4:
                clearScreen();

                puts("El Crupier cambiará algunas cartas: \n");

                juegaCrupier(&mesa, 0);

                puts("El Crupier ya cambió sus cartas. Es tu turno.\n");
                calcularYActualizarPuntos(&mesa.manoUno);

                pressToContinue();
                clearScreen();

                char quiereCambio;
                int index = -1;
                int changedValues[3] = {-1, -1,-1};

                for (int i=0; i<3; i++) {
                    clearScreen();
                    puts("Tus cartas son: ");
                    mostrarMano(mesa.manoDos);
                    evaluaUnaMano(&mesa.manoDos);

                    printf("¿Quieres cambiar %s carta? [y/n]: ", i == 0 ? "una" : "otra");
                    scanf(" %c", &quiereCambio);

                    if (quiereCambio == 'y') {
                        printf("¿Qué carta quieres cambiar? [1-5]: ");
                        scanf(" %d", &index);
                        index--;

                        if (arrayContainsValue(index, 3, changedValues)) {
                            puts("No puedes cambiar la misma carta, intenta con otra");
                            i--;
                            continue;
                        }

                        if (index < 0 || index > 5) {
                            puts("Ingresa una carta válida [1-5]");
                            i--;
                            continue;
                        }

                        cambiarCarta(&mesa, JugadorDos, index);
                        changedValues[i] = index;
                    } else{
                        break;
                    }
                }

                clearScreen();

                puts("Las cartas del Crupier son: ");
                mostrarMano(mesa.manoUno);
                evaluaUnaMano(&mesa.manoUno);

                puts("Tus cartas son: ");
                mostrarMano(mesa.manoDos);
                evaluaUnaMano(&mesa.manoDos);

                evaluarMesa(&mesa);

                pressToContinue();
                clearScreen();

                break;

        }
    }

    clearScreen();
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
