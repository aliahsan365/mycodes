subcjto([],[]).  %subcjto(L,S) significa "S es un subconjunto de L".
subcjto([X|C],[X|S]):-subcjto(C,S).
subcjto([_|C],S):-subcjto(C,S).

esta_ordenada([]).
esta_ordenada([_]) :- !.
esta_ordenada([X,Y|L]) :- X =< Y, esta_ordenada([Y|L]).

suma([],0).
suma([X|L],S) :- suma(L,S1), S is S1+X.

creciente_suma(L,K,S):-
    subcjto(L,S),
    esta_ordenada(S),
    suma(S,K).
