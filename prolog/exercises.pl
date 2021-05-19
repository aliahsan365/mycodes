%ex2 : P es el producto de la lista L
prod([],1).
prod([X|L],P):- prod(L,P1), P is P1*X.


%ex2 P es el producto escalar de la lista L1 con L2
pescalar([],[],1).
pescalar([X|L1],[Y|L2],P):- pescalar(L1,L2,P1), P is P1 + X*Y.


% X es miembro de la lista L.
mymember(X,[X|_]):-!.
mymember(X,[_|L]):- mymember(X,L).


%ex4 U es la union del conjunto L1 con conjunto  L2
union([],L,L).
union([X|L1],L2,U):- mymember(X,L2),!,union(L1,L2,U).
union([X|L1],L2,[X|U]):- union(L1,L2,U). 
%U es la intersecion del conjunto L1 con conjunto  L2
intersec([],_,[]):-!.
intersec([X|L1],[X|L2],[X|U]):- intersec(L1,L2,U),!.
intersec([_|L1],L2,U):- intersec(L1,L2,U).


%ex5 X es el ultimo de elemento de la lista L
ultimo(X,L):- concat(_,[X],L),!.


% L3 es la concatenacion de la`lista`L1 con`la`lista` L2.
concat([],L,L).
concat([X|L1], L2,[X|L3]):- concat(L1,L2,L3).


% LF es el inverso de la lista L.
inverso([],[]).
inverso([X|L],LF):- inverso(L,LR), concat(LR,[X],LF).

%ex6 F es el N-essimo numero de la serie de fibonacci
fib(0,1).
fib(1,1).
fib(N,F):- N > 1, N1 is N-1, N2 is N-2, 
		   fib(N1,F1),fib(N2,F2),
		   F is F1+F2,!.



% S es la suma de la lista L.
suma_lista([],0).
suma_lista([X|L],S):- suma_lista(L,S1), S is S1+X.


%ex7 L son los resultados de las N tiradas de dados del 1 al 6 que sumen P puntos en total.
dados(0,0,[]).
dados(P,N,[X|L]):- N>0,
				   member(X,[1,2,3,4,5,6]),
				   P1 is P-X,
				   N1 is N-1,
				   dados(P1,N1,L).
				   

%ex8 L tiene algun elemento que es igual a la suma de la lista restante
suma_demes(L):- pert_con_resto(X,L,Resto),suma_lista(Resto,X),!.



% La lista L esta ordenada
esta_ordenada([_]):-!.
esta_ordenada([X,Y|L]):- Y >= X, esta_ordenada([Y|L]).


% La ordenacion de la lista L1 es la lista L2
ordenacion(L1,L2):- permutation(L1,L2), esta_ordenada(L2).




%Resto es la lista  L sin el elemento X
pert_con_resto(X,L,Resto):- concat(L1,[X|L2],L), concat(L1,L2,Resto).


% La lista L es la descompocion en factores primos del numero N.
dpf(1,[1]):-!.
dpf(N,[F|L]):- 
	N > 1, 
	between(2,N,F), 
	0 is N mod F,!, 
	N1 is N // F,
	dpf(N1,L).

%N es el minimo comun multiplo entre el elemento X y el elemento Y.
mcm(1,_,1):-!.
mcm(_,1,1):-!.
mcm(X,Y,N):-between(2,X,N), between(2,Y,N), 0 is X mod N, 0 is Y mod N, !.


%N es maximo comun divisor entre el elemento X y el elemento Y.
mcd(X,0,X):-!.
mcd(X,Y,N):- Y1 is X mod Y , mcd(Y,Y1,N),!.





% S son las ocurencia del elemento X en la lista L.
ocurencias(_,[],0).
ocurencias(X,[X|L],S):- ocurencias(X,L,S1), S is S1+1,!.
ocurencias(X,[_|L],S):- ocurencias(X,L,S).




card(L):- card2(L,C), sinRepetidos(C,CR), write(CR).


card2([],[]).
card2([X|L],[[X,N]|Car]):- card2(L,Car), ocurencias(X,[X|L],N).


%sinRepedtidos(L,LR). LR es L sin elementos repetidos

sinRepetidos([],[]).
sinRepetidos([X|L],[X|LR]):- 
	pert_con_resto(X,[X|L],R),
	\+member(X,R),!,
	sinRepetidos(L,LR).
sinRepetidos([_|L], LR):-
	sinRepetidos(L,LR).



%suma_ants(L),dada una lista de enteros L, se satisface si existe alg´un elemento en 
%L que es igual a la suma de los elementos anteriores a ´el en L
suma_ants(L):- append(L1,[X|_],L), suma_lista(L1,X),!.

%insercion(X,L1,L2), L2 es la lista obtenida al insertar X en su sitio 
%en la lista de enteros L1 que estaa ordenada de menor a mayor

%insercion(X,[],[X]).
%insercion(X,[Y|L1],L2):- Y > X,!,insercion(X,L1,LIO),append(LIO,[Y|L1],L2).		  
%insercion(X,[Y|L1],L2):-  insercion(X,L1,LIO),!, append([Y],LIO,L2).		   




insercion(X,[],[X]).
insercion(X,[Y|L1],[Y,X|L1]):- X =< Y.  
insercion(X,[Y|L1],[Y|L2]):- X>Y,insercion(X,L1,L2).	

	   
%isort(L1,L2) L2 es L1 ordenado (mediante inserciones : insertion_sorting algorithm in prolog)
isort([],[]).
isort([X|L],LO):- isort(L,LOC), insercion(X,LOC,LO).




%merge sort 



lsize([],0).
lsize([_|L], N):- lsize(L,N1), N is N1+1.


cremallera(L1,[],L1):-!.
cremallera([],L2,L2):-!.
cremallera([X|L1],[Y|L2],[X,Y|L3]):- cremallera(L1,L2,L3).


%smerge([],[]).
%smerge([X|L1],L2):-  lsize(L1,N),
%				 N > 1,!,
%				 concat(L1D,L1I,L1),
%				 smerge(L1D,L2D),
%				 smerge(L1I,L2I),
%				 cremallera(L2D,L2I,L2).
%smerge(L1,L1).





%palindromos(L) todos los palindromo que podamos formar de L con L.


%dosPartes(L,L1,L2):- append(L1,L2,L), lsize(L1,N), lsize(L2,N),!. 




%capicuas([]).
%capicuas(L):- dosPartes(L,L1,L2), reverse(L2,LR), LR is L1,!.  



%esPalindromo(L,P):- permutation(L,P), capicuas(P), !. 


%palindromos(L):- esPalindromo(L,LP), write(LP), fail.


es_palindromo([]).
es_palindromo([_]) :- !. % regla adecuada
es_palindromo([X|L]) :- concat(L1,[X],L), es_palindromo(L1). 



palindromos(L) :- permutacion(L,P), es_palindromo(P), 
  write(P), nl, fail. 
palindromos(_). 



mypertconresto(X,L,R):- append(L1,[X|L2],L) , append(L1,L2,R),!.




