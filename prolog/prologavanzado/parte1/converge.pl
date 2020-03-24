%ex1
%S es la suma de cuadrados del numero N
sumaCuadrados(0,0):-!.
sumaCuadrados(N,S):- 
	N1 is N//10,
	sumaCuadrados(N1,S1),
	R is N mod 10,
	S is S1+R*R.

ciclo(N,L):- member(N,L).


%44 32 13 10 1

converge(1):-!.
converge(N):-
	sumaCuadrados(N,S),
	converge(S),!,
	not(ciclo(N,[S])).



	
	

