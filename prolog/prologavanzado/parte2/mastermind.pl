samee([],[],0,[]).
samee([X|L1],[X|L2],N,[X|LE]):-
	N1 is N - 1,
	samee(L1,L2,N1,LE),!.
samee([_|L1],[_|L2],N,LE):-
	N1 is N - 1,
	samee(L1,L2,N1,LE),!.


mylistsize([],0).
mylistsize([_|L],S):-mylistsize(L,S1), S is  S1+1.


eliminaX(_,[],[]).
eliminaX(X,[X|L],LSX):- eliminaX(X,L,LSX),!.
eliminaX(X,[Y|L],[Y|LE]):-eliminaX(X,L,LE).

eliminal([],_,[]).
eliminal(L,[X|LE],LT):-
	eliminaX(X,L,LSX),
	eliminal(LSX,LE,LT),!.
eliminal(L,[],L).





pert_con_resto(X,L,Resto):- append(L1,[X|L2],L), append(L1,L2,Resto).



communes(_,[],0).
communes(C,[Col|I],X):-
	pert_con_resto(Col,C,R),
	communes(R,I,X2),
	X is X2+1.
communes(C,[_|I],X):-
communes(C,I,X).


respuesta(C,I,E,D):- 
	mylistsize(C,N),
	mylistsize(I,N),
	samee(C,I,N,LE),
	mylistsize(LE,E),
	communes(C,I,D1),
	D is D1-E,!.