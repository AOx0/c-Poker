build:
	gcc Carta.c Carta.h Crupier.c Crupier.h Mano.c Mano.h Mesa.c Mesa.h Puntos.c Puntos.h main.c
	rm Carta.h.gch Crupier.h.gch Mano.h.gch Mesa.h.gch Puntos.h.gch
	mv a.out poker