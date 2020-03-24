tablero(8).

unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 - 2, J2 is J1+1,between(0,N,I2),between(0,N,J2),!.
unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 - 2, J2 is J1-1,between(0,N,I2),between(0,N,J2),!.

unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 - 1, J2 is J1-2,between(0,N,I2),between(0,N,J2),!. 
unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 - 1, J2 is J1+2,between(0,N,I2),between(0,N,J2),!.

unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 + 1, J2 is J1+2,between(0,N,I2),between(0,N,J2),!. 
unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 + 1, J2 is J1-2,between(0,N,I2),between(0,N,J2),!.

unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 + 2, J2 is J1-1,between(0,N,I2),between(0,N,J2),!. 
unPaso([I1,J1],[I2,J2]):- tablero(N),I2 is I1 + 2, J2 is J1+1,between(0,N,I2),between(0,N,J2),!. 


camino(E,E,C,C).
camino(EstadoActual, EstadoFinal, CaminoHastaAhora,CaminoTotal):-
  unPaso(EstadoActual,EstSiguiente),
  \+member(EstSiguiente,CaminoHastaAhora),
  camino(EstSiguiente, EstadoFinal,[EstSiguiente|CaminoHastaAhora],CaminoTotal).
 
nat(0).
nat(N):- nat(M), N is M + 1. 
 
 
solucionOptima:-
	nat(N),
    camino([0,0],[0,4],[[0,0]],C),
	length(C,N),
	reverse(C,CR),
	write(CR).
	
 caballos:- solucionOptima,!.
