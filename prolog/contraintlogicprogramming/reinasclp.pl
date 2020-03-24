:- use_module(library(clpfd)).

% i + j = k + l 
diagonalesS(_,_,[],_).
diagonalesS(X,N,[Y|L],N1):- 
	X + N #\= Y + N1,
	N2 is N1 - 1,
    diagonalesS(X,N,L,N2).

% i - j = k - l 
diagonalesR(_,_,[],_).
diagonalesR(X,N,[Y|L],N1):- 
	X - N #\= Y - N1,
	N2 is N1 - 1,
    diagonalesR(X,N,L,N2).

diagonales([],_).
diagonales([X|L],N):-
    N1 is N - 1,
    diagonalesS(X,N,L,N1),
    diagonalesR(X,N,L,N1),
 	diagonales(L,N1). 

%solo cambiar el numero en el tablero para que funcion con una N diferente
tablero(14).
%ahora mismos pinta en el tablero todas las soluciones
% L = [R1,R2,R3,R4,R5,R6,R7,R8]
reinas:- tablero(N),
 		 length(Vars,N),
 		 Vars ins 1..N,
 		 all_different(Vars),
 		 %restringue tanto las superaires como las inferiores.
 		 diagonales(Vars,N),nl,
 		 label(Vars),
         pintatab(N,Vars),
 		 nl,fail. 
reinas.




pintatab(0,_):-!.
pintatab(N,[X|L]):- N >0, tablero(T), pinta(T,X), nl, N1 is N-1, pintatab(N1,L).

%pinta N-1 puntos , si es reina pinta x.
pinta(0,_):-!.
pinta(N,X):- N>0, N1 is N-1, pinta(N1,X), N \= X, !, write('. ').
pinta(_,_):- write('x '),!.

