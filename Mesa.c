/*
 * @Mesa.c
 *
 * @brief Archivo de código fuente para los prototipos definidos en "Mesa.h".
 *
 * Define la estructura Mesa, que consiste de dos Manos y una baraja de Carta, y las funciones necesarias para el
 * contexto de mesa, cuál es el ganador, anunciar el ganador, hacer cambio de cartas, etc.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#include <stdio.h>
#include <string.h>
#include "Mesa.h"

/*
 * Función que obtiene la carta más alta de una mano siempre y cuando no sea parte de los valores descartados. Se usa
 * para poder desempatar manos donde ambos tiene la misma carta como la más alta. El método actualiza los meta datos de
 * la mano y además devuelve la carta más alta.
 *
 * @param mano La mano de la cual se quiere encontrar la segunda/tercera/cuarta/quinta carta más alta.
 * @return La nueva Carta más alta
 */

Carta masAltaExcepto(Mano *mano, int valores[5]) {
    int mayor=0, i_mayor=0;
    for (int i=0; i <5; i++)
        if (mano->cartas[i]->valor > mayor && !arrayContainsValue(mano->cartas[i]->valor, 5, valores)) {
            mayor = mano->cartas[i]->valor;
            i_mayor = i;
        }

    mano->masAlta = *mano->cartas[i_mayor];
    return *mano->cartas[i_mayor];
}

/*
 * Función que determina el ganador de la mesa.
 *
 * Primero compara la calidad de la jugada de ambas manos e intenta elegir a partir de eso el ganador.
 * Si ambos tienen la misma jugada intenta decidir el ganador con la cart más alta de entre las dos manos.
 * Si ambos tienen la misma carta más grande, analiará cuantas veces sean necesarias para encontrar cuál de las manos
 * tiene la segunda/tercera/cuarta/quinta carta más alta.
 *
 * @param mesa La mesa de la cual se desea encontrar el ganador.
 * @return el Jugador que gana de la mesa. Existe la posibilidad de que sea un empate.
 */
Jugador determinarGanador_(Mesa *mesa) {

    if ((int)mesa->manoUno.puntos > (int)mesa->manoDos.puntos) return JugadorUno;
    if ((int)mesa->manoUno.puntos < (int)mesa->manoDos.puntos) return JugadorDos;


    int altosDescartadosMano1[5] = {-1,-1,-1,-1};
    int altosDescartadosMano2[5] = {-1,-1,-1,-1};

    for (int i=0; i<5; i++) {
        altosDescartadosMano1[i] = masAltaExcepto(&mesa->manoUno, altosDescartadosMano1 ).valor;
        altosDescartadosMano2[i] = masAltaExcepto(&mesa->manoDos, altosDescartadosMano2 ).valor;

        if ((int)mesa->manoUno.masAlta.valor > (int)mesa->manoDos.masAlta.valor) return JugadorUno;
        if ((int)mesa->manoUno.masAlta.valor < (int)mesa->manoDos.masAlta.valor) return JugadorDos;
    }


    return None;
}

/*
 * Procedimiento que actualiza el meta dato de la Mano que indica el ganador. Para hacerlo llama a determinarGanador_
 *
 * @param mesa La mesa de la cual se desea encontrar el ganador. Es un apuntador para que pueda ser modificada y ver
 * los cambios reflejados
 */

void determinarGanador(Mesa  * mesa) {
    mesa->ganador = determinarGanador_(mesa);
}

/*
 * Procedimiento que lee el meta dato ganador de la instancia Mesa y de acuerdo a su valor imprime quién es el ganador
 *
 * @param mesa La mesa de la cual se desea mostrar su ganador en la consola
 */
void mostrarGanador(Mesa *mesa) {

    printf("La mano ganadora es "
        "%s\n", mesa->ganador == JugadorUno ? "la 1 (Crupier)" :  mesa->ganador == JugadorDos ? "la 2 (Tu)" : "Empate"
    );
}

/*
 * Procedimiento que le cambia la carta indicada al jugador indicado, asignándole la carta de "hasta arriba" de la
 * baraja, la cual es totalmente aleatoria.
 * El método también actualiza el meta dato deckIndex, que indica cuál es la carta de hasta arriba en la baraja.
 *
 * @param mesa La mesa a la que pertenece el jugador.
 * @param jugador El jugador que desea cambiar su carta. Los valores válidos son JugadorUno y JugadorDos, del enum Jugador
 * @param i El número de carta que desea cambiar el jugador, representa el índice en la lista de cartas de su mano.
 */
void cambiarCarta(Mesa * mesa, Jugador jugador, int i) {
    if (jugador == JugadorUno) mesa->manoUno.cartas[i] = &mesa->deck[mesa->deckIndex];
    else mesa->manoDos.cartas[i] = (Carta *) &mesa->deck[mesa->deckIndex];

    mesa->deckIndex-=1;
}

/*
 * Constructor de una instancia de Mesa, almacena la baraja de la mesa, la mano del jugador uno, la mano del jugador dos,
 * y meta datos de utilidad como el índice de la carta que está hasta arriba de la baraja para ser la próxima en ser despachada
 * o cuál de los dos jugadores es el ganador de la mesa.
 *
 * @param deck La lista de cartas que ya fue mezclada, de ella se formaron las manos 1 y 2 y de ella se extraen las cartas
 * que los jugadores desean cambiar tomando las que están al final de la misma.
 * @param mano1 La mano del jugador uno, siempre será la del Crupier
 * @param mano2 La mano del jugador dos, ésta es la mano del ususario
 *
 * @return una instancia de Mesa con la información de la misma
 */
Mesa crearMesa(Carta   deck[13 * 4], Mano mano1, Mano mano2) {
    Mesa mesa = {
        .deck =  0,
        .manoUno = mano1,
        .manoDos = mano2,
        .ganador = None,
        .deckIndex = 41
    };

    memcpy(mesa.deck, deck, (13*4)*(sizeof (Carta)));

    return mesa;
}