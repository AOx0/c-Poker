//
// Created by Alejandro D on 01/12/21.
//

#include "Crupier.h"

void JuegaCrupier(Mano * mano) {

    switch (mano->puntos) {
        case EscaleraReal:
        case Escalera:
        case EscaleraDeColor:
        case Color:
        case Full:
            return;
        default:
            break;
    }

    for (int i=0; i<3; i++) {

    }


}