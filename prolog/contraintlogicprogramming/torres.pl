:- use_module(library(clpfd)).


tablero(4).

pintatab(0,_):-!.
pintatab(N,[X|L]):- N >0, tablero(T), pinta(T,X), nl, N1 is N-1, pintatab(N1,L).

pinta(0,_):-!.
pinta(N,X):- N>0, N1 is N-1, pinta(N1,X), N \= X, !, write('+').
pinta(_,_):- write('T'),!.






myAllDifferentAux(_,[]).
myAllDifferentAux(X,[Y|L]):- X #\= Y, myAllDifferentAux(X,L).


myalldifferrent([]).
myalldifferrent([X|L]):- myAllDifferentAux(X,L), myalldifferrent(L).



myalldifferrentproaux(_,[],[]).
myalldifferrentproaux(X,[Y|L],[X #\= Y|LE]):- 
		X #\= Y,
		myalldifferrentproaux(X,L,LE). 


myalldifferrentpro([],[]).
myalldifferrentpro([X|L],[E|LE]):-
    myalldifferrentproaux(X,L,E),
    myalldifferrentpro(L,LE).
myalldifferrentpro([_],_).
  






 torres:- tablero(N),
 		  length(Vars,N),
 		  Vars ins 1..N,
 		  %myalldifferrent(Vars,LE), 
          %myalldifferrentpro(Vars,LE),
 		  %write(LE), 
 		  %nl,
          all_different(Vars),
          label(Vars),
          pintatab(N,Vars),
 		  nl,
 		  fail. 
torres.


