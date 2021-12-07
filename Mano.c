/*
 * @Mano.c
 *
 * @brief Archivo de código fuente para los prototipos definidos en "Mano.h".
 *
 * El archivo contiene los métodos que calculan el tipo de jugada, analiza cuál es la carta más alta, su posición en el
 * arreglo de Carta de la mano, etc.
 *
 * En resumen, todos los métodos necesarios para tratar la estructura Mano, almacenando información útil.
 *
 * @author AOx0
 * @date 30/11/2021
 */

#define bool int

#include <string.h>
#include "Mano.h"
#include "Puntos.h"

/*
 * Función que analiza el tipo de jugada que es una mano y devuelve su resultado.
 * @param mano La mano que analizará
 * @return Posibilidad de enum Puntos que representa el tipo de jugada y a su vez cuánto vale
 */
Puntos calcularPuntos(Mano * mano) {
    if (esEscaleraReal(mano)) return EscaleraReal;
    else if (esEscaleraDeColor(mano)) return EscaleraDeColor;
    else if (esPoquer(mano)) return Poquer;
    else if (esFull(mano)) return Full;
    else if (esColor(mano)) return Color;
    else if (esEscalera(mano)) return Escalera;
    else if (esTrio(mano)) return Trio;
    else if (esDoblePareja(mano)) return DoblePareja;
    else if (esPareja(mano)) return Pareja;
    else {esMasAlta(mano); return Jardin;}
}

/*
 * Procedimiento que calcula el tipo de jugada de una mano y actualiza la información de la misma para reflejar
 * el cálculo.
 *
 * @param mano La mano que analizará
 */
void calcularYActualizarPuntos(Mano * mano) {
    mano->puntos = calcularPuntos(mano);
}

/*
 * Función encargada de crear una instancia de Mano, que es una estructura que almacena 5 instancias de Carta junto con
 * información de interés de las mismas.
 *
 * La función se encarga de calcular la información de interés de la mano, como la carta más alta y su número, la carta
 * más baja y su número, analiza si todas las cartas son de la misma figura, hace un primer análisis del tipo de jugada,
 * etc.
 *
 * @param cartas Arreglo de 5 cartas que representan la mano en sí.
 * @return Instancia creada de Mano
 */
Mano crearMano(Carta cartas[5]) {

    Mano mano = {
            &cartas[0],
            &cartas[1],
            &cartas[2],
            &cartas[3],
            &cartas[4],
        .sonMismaFigura = 1,
        .numCartasUtiles = 0,
    };

    Figura primera;

    // Analiza si todas las cartas son de la misma figura.
    for (int i=0; i <5; i++) {
        if (i==0) primera = mano.cartas[i]->figura;
        if (mano.cartas[i]->figura != primera) mano.sonMismaFigura = 0;
    }


    // Busca la carta más alta
    int mayor=0, i_mayor=0;
    for (int i=0; i <5; i++) if (mano.cartas[i]->valor > mayor) {mayor = mano.cartas[i]->valor; i_mayor = i;}

    mano.masAlta = cartas[i_mayor];
    mano.i_masAlta = i_mayor;

    // Busca la carta más baja
    int masBaja=9999,  i_menor=0;
    for (int i=0; i <5; i++) if (mano.cartas[i]->valor < masBaja) {masBaja = mano.cartas[i]->valor; i_menor = i;}

    mano.masBaja = cartas[i_menor];
    mano.i_masBaja = i_menor;

    calcularYActualizarPuntos(&mano);

    return mano;
}

/*
 * Procedimiento que muestra las cartas que componen una mano. Es un bucle que ejecuta imprimirCarta para cada una de
 * las 5 cartas de la mano.
 *
 * @param mano La mano que se desea mostrar en la consola
 */
void mostrarMano(Mano mano) {
    for (int i=0; i <5; i++) {imprimirCarta(*mano.cartas[i]); }
}

/*
 * Función útil que devuelve 1 si un arreglo de valores `int` de tamaño `size` contiene o no el valor indicado.
 *
 * @param valor El valor del que se desea saber si está contenido en el arreglo de valores
 * @param size El tamaño del arreglo de valores de los que se quiere comparar si valor está entre ellos. Hay que tener
 * cuidado de pasar un tamaño adecuado o habrá leaks de memoria.
 * @param array El arreglo de valores de los cuales se desea saber si el valor está entre ellos
 *
 * @return El valor 1 si sí está contenido en el arreglo el valor o 0 si no es asi.
 */
bool arrayContainsValue(int valor, int size, const int array[size] ) {
    if (size == 0) return 0;

    for (int i=0; i<size; i++) {
        if (array[i] == valor) {
            return 1;
        }
    }

    return 0;
}

/*
 * Función que analiza si un valor está contenido en una Mano, revisando los valores de cada una de las 5 cartas.
 * @param mano La mano que se desea analizar.
 * @param valor El valor que se desea comprobar si está contenido entre las cartas de la mano.
 *
 * @return El valor 1 si sí está contenido en las cartas el valor o 0 si no es asi.
 */
bool containsValue(Mano mano, Valor valor ) {
    for (int i=0; i<5; i++) {
        if (mano.cartas[i]->valor == valor) {
            return 1;
        }
    }

    return 0;
}


/*
 * Función que analiza si una serie de valores están contenidos en una Mano. Util para revisar si una mano es cualquier
 * tipo de escalera, es decir, cuando se conoce el valor que deben tener las 5 cartas y cada uno es distinto. No puede
 * diferenciar entre valores similares.
 *
 * @param mano La mano a ser analizada
 * @param valores Los valores que deben estar contenidos en la mano para devolver 1
 *
 *  @return El valor 1 si sí están contenidos los valores en la mano o 0 si no es asi.
 */
bool containsValues(Mano mano,  Valor valores[5]  ) {
    int result = 0;
    for (int i=0; i<5; i++) {
        result += containsValue(mano, valores[i]);
    }

    if (result == 5) return 1;

    return 0;
}

/*
 * Función que analiza si una mano es una escalera real. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es una escalera real o 0 si no lo es
 */
bool esEscaleraReal(Mano * mano) {
    Valor valores[] = {Diez, As, Rey, Reina, Jota};
    if ( mano->sonMismaFigura && containsValues(*mano, valores) ) {
        int indices[] = {0,1,2,3,4};
        mano->numCartasUtiles = 5;
        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    }
    return 0;
}

/*
 * Función que analiza si una mano es una escalera de color. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es una escalera real o 0 si no lo es
 */
bool esEscaleraDeColor(Mano * mano) {
    for (int i=2; i<=14; i++){
        Valor valores[] = {(Valor)i, (Valor)(i+1), (Valor)(i+2), (Valor)(i+3), (Valor)(i+4)};
        if ( mano->sonMismaFigura && containsValues(*mano, valores) ) {
            int indices[] = {0,1,2,3,4};
            mano->numCartasUtiles = 5;
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }
    return 0;
}

/*
 * Función que analiza si una mano es un póquer. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un póquer o 0 si no lo es
 */
bool esPoquer(Mano * mano) {
    int timesFound;
    int indices[] = {-1,-1,-1,-1,-1};
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) {
            if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
                indices[timesFound] = j;
                timesFound++;
            }
        }
        if (timesFound == 4) {
            mano->numCartasUtiles = 4;
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }

    return 0;
}

/*
 * Función que analiza si una mano es un full. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un full o 0 si no lo es
 */
bool esFull(Mano * mano) {
    int timesFound;
    int found = 0;
    Valor TerciaDeValor;

    // Busca la tercia
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) timesFound++;
        if (timesFound == 3) {
            found = 1;
            TerciaDeValor = mano->cartas[i]->valor;
            break;
        }
    }

    // Busca el par
    if (found) {
        for (int i=0; i<5; i++){
            if (mano->cartas[i]->valor == TerciaDeValor) continue;
            timesFound=0;
            for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) timesFound++;
            if (timesFound == 2) {
                int indices[] = {0,1,2,3,4};
                mano->numCartasUtiles = 5;
                memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
                return 1;
            }
        }
    }

    return 0;
}

/*
 * Función que analiza si una mano es un Color. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un color o 0 si no lo es
 */
bool esColor(Mano * mano) {
    if (mano->sonMismaFigura) {
        int indices[] = {0,1,2,3,4};
        mano->numCartasUtiles = 5;
        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    }
    return 0;
}

/*
 * Función que analiza si una mano es una escalera. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es una escalera o 0 si no lo es
 */
bool esEscalera(Mano * mano) {
    for (int i=2; i<=14; i++){
        Valor valores[] = {(Valor)i, (Valor)(i+1), (Valor)(i+2), (Valor)(i+3), (Valor)(i+4)};
        if (containsValues(*mano, valores) ) {
            int indices[] = {0,1,2,3,4};
            mano->numCartasUtiles = 5;
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }
    return 0;
}

/*
 * Función que analiza si una mano es un trio. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un trio o 0 si no lo es
 */
bool esTrio(Mano * mano) {
    int indices[] = {-1,-1,-1,-1,-1};
    int timesFound;

    // Busca por 3 cartas con el mismo valor
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
            indices[timesFound] = j;
            timesFound++;
        }


        if (timesFound == 3) {
            mano->numCartasUtiles = 3;
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }

    return 0;
}

/*
 * Función que analiza si una mano es un doble par. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un doble par o 0 si no lo es
 */
bool esDoblePareja(Mano * mano) {
    int timesFound;
    int found = 0;
    int indices[] = {-1,-1,-1,-1,-1};
    Valor ParDeValor;

    // Busca el primer par y recuerda el valor de las cartas que lo conforman
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
            indices[timesFound] = j;
            timesFound++;
        }

        if (timesFound == 2) {
            found = 1;
            ParDeValor = mano->cartas[i]->valor;
            break;
        }
    }

    // Busca el segundo par, ignorando las cartas con el valor del primer par
    if (found) {
        for (int i=0; i<5; i++){
            if (mano->cartas[i]->valor == ParDeValor) continue;
            timesFound=2;
            for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
                    indices[timesFound] = j;
                    timesFound++;
                }

            if (timesFound == 4){
                mano->numCartasUtiles = 4;
                memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
                return 1;
            }
        }
    }

    return 0;
}

/*
 * Función que analiza si una mano es un par. Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return 1 si es un par o 0 si no lo es
 */
bool esPareja(Mano * mano) {
    int timesFound ;
    int found = 0;
    int indices[] = {-1,-1,-1,-1,-1};
    Valor ParDeValor;

    //  Busca por un par
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
            indices[timesFound] = j;
            timesFound++;
        }
        if (timesFound == 2) {
            found = 1;
            ParDeValor = mano->cartas[i]->valor;
            break;
        }
    }

    int tresRestantes[3] = {-1,-1,-1};
    int j = 0;

    // Se asegura que el resto sean diferentes.
    if (found) {
        for (int i=0; i<5; i++ ){
            if (mano->cartas[i]->valor == ParDeValor) { continue; }
            if ( arrayContainsValue(mano->cartas[i]->valor, j, tresRestantes) ) return 0;
            tresRestantes[j] = mano->cartas[i]->valor;
            j++;
        }
        mano->numCartasUtiles = 2;
        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    } else {
        return 0;
    }

}

/*
 * Función que analiza si una mano es un Jardín (que no es nada). Si es que se trata de una entonces devuelve 1 y cambia los
 * meta datos de la mano para incluir un poco más de información útil directamente relacionados al tipo de jugada, como
 * lo es las cartas útiles (que componen la jugada) y el número de cartas útiles.
 *
 * @param mano La mano a ser analizada, es un apuntador para poder modificarlo y que se vea reflejado
 * @return Devuelve la carta más grande de la Mano y almacena en sus meta datos que es la única carta útil
 */
Carta esMasAlta(Mano * mano) {
    int indices[5] = {mano->i_masAlta, -1,-1,-1,-1};
    memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
    return mano->masAlta;
}
