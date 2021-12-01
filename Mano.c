//
// Created by Alejandro D on 29/11/21.
//

#include <libc.h>
#include "Mano.h"
#include "Puntos.h"


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

Mano crearMano(Carta cartas[5]) {

    Mano mano = {
            &cartas[0],
            &cartas[1],
            &cartas[2],
            &cartas[3],
            &cartas[4],
        .sonMismaFigura = 0,
        .masAlta =  cartas[0]
    };

    int primera = -1;
    int suma = 0;
    for (int i=0; i <5; i++) {
        if (i==0) primera = (int)mano.cartas[i]->figura + 1;
        suma += (int)mano.cartas[i]->figura + 1;
    }

    if ((double)suma/(double)primera == 5.0){
        mano.sonMismaFigura = 1;
    }

    int mayor=0, i_mayor=0, i;
    for (i=0; i <5; i++) if (mano.cartas[i]->valor > mayor) {mayor = mano.cartas[i]->valor; i_mayor = i;}

    mano.masAlta = cartas[i_mayor];
    mano.i_masAlta = i_mayor;

    mano.puntos = calcularPuntos(&mano);

    return mano;


}

void mostrarMano(Mano mano) {
    for (int i=0; i <5; i++) {imprimirCarta(*mano.cartas[i]); }
}

int arrayContainsValue(int valor, int size, const int array[size] ) {
    if (size == 0) return 0;

    for (int i=0; i<5; i++) {
        if (array[i] == valor) {
            return 1;
        }
    }

    return 0;
}

int containsValue(Mano mano, Valor valor, int exceptSize,  int exceptArray[exceptSize] ) {
    for (int i=0; i<5; i++) {
        if (mano.cartas[i]->valor == valor && !arrayContainsValue(mano.cartas[i]->valor, exceptSize, exceptArray)) {
            return 1;
        }
    }

    return 0;
}






int containsValues(Mano mano,  int valoresSize, Valor valores[valoresSize], int exceptSize,  int exceptArray[exceptSize]  ) {
    int result = 0;
    for (int i=0; i<valoresSize; i++) {
        result += containsValue(mano, valores[i], exceptSize, exceptArray);
    }

    if (result == 5) return 1;

    return 0;
}

int esEscaleraReal(Mano * mano) {
    Valor valores[] = {Diez, As, Rey, Reina, Jota};
    if ( mano->sonMismaFigura && containsValues(*mano, 5, valores, 0, 0 ) ) {
        int indices[] = {0,1,2,3,4};
        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    }
    return 0;
}

int esEscaleraDeColor(Mano * mano) {
    for (int i=2; i<=14; i++){
        Valor valores[] = {(Valor)i, (Valor)(i+1), (Valor)(i+2), (Valor)(i+3), (Valor)(i+4)};
        if ( mano->sonMismaFigura && containsValues(*mano, 5, valores, 0, 0) ) {
            int indices[] = {0,1,2,3,4};
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }
    return 0;
}

int esPoquer(Mano * mano) {
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
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }

    return 0;
}

int esFull(Mano * mano) {
    int timesFound;
    int found = 0;
    Valor TerciaDeValor;
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) timesFound++;
        if (timesFound == 3) {
            found = 1;
            TerciaDeValor = mano->cartas[i]->valor;
            break;
        }
    }

    if (found) {
        for (int i=0; i<5; i++){
            if (mano->cartas[i]->valor == TerciaDeValor) continue;
            timesFound=0;
            for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) timesFound++;
            if (timesFound == 2) {
                int indices[] = {0,1,2,3,4};
                memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
                return 1;
            }
        }
    }

    return 0;
}

int esColor(Mano * mano) {
    if (mano->sonMismaFigura) {
        int indices[] = {0,1,2,3,4};
        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    }
    return 0;
}

int esEscalera(Mano * mano) {
    for (int i=2; i<=14; i++){
        Valor valores[] = {(Valor)i, (Valor)(i+1), (Valor)(i+2), (Valor)(i+3), (Valor)(i+4)};
        if (containsValues(*mano, 5, valores, 0, 0) ) {
            int indices[] = {0,1,2,3,4};
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }
    return 0;
}

int esTrio(Mano * mano) {
    int indices[] = {-1,-1,-1,-1,-1};
    int timesFound;
    for (int i=0; i<5; i++){
        timesFound=0;
        for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
            indices[timesFound] = j;
            timesFound++;
        }
        if (timesFound == 3) {
            memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
            return 1;
        }
    }

    return 0;
}

int esDoblePareja(Mano * mano) {
    int timesFound;
    int found = 0;
    int indices[] = {-1,-1,-1,-1,-1};
    Valor ParDeValor;
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

    if (found) {
        for (int i=0; i<5; i++){
            if (mano->cartas[i]->valor == ParDeValor) continue;
            timesFound=2;
            for (int j=0; j<5; j++) if (mano->cartas[j]->valor == mano->cartas[i]->valor) {
                    indices[timesFound] = j;
                    timesFound++;
                }
            if (timesFound == 4){
                memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
                return 1;
            }
        }
    }

    return 0;
}

int esPareja(Mano * mano) {
    int timesFound ;
    int found = 0;
    int indices[] = {-1,-1,-1,-1,-1};
    Valor ParDeValor;

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

    if (found) {
        for (int i=0; i<5; i++ ){
            if (mano->cartas[i]->valor == ParDeValor) { continue; }
            if ( arrayContainsValue(mano->cartas[i]->valor, j, tresRestantes) ) return 0;
            tresRestantes[j] = mano->cartas[i]->valor;
            j++;
        }

        memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
        return 1;
    } else {
        return 0;
    }

}

Carta esMasAlta(Mano * mano) {
    int indices[5] = {mano->i_masAlta, -1,-1,-1,-1};
    memcpy(&mano->i_cartasUtiles, indices, 5*sizeof(int));
    return mano->masAlta;
}