:-use_module(library(clpfd)).

nVertices(5).
edge(1,2).
edge(1,3).
edge(2,3).
edge(3,4).
edge(4,5).
edge(5,1).
edge(5,2).

displaySolCol(Vars):-
    nVertices(N),
    between(1,N,V),
    nth1(V,Vars,X), %% X is the V-th element of the list Vars (first element has index 1)
    write('Color('), write(V), write(') = '), write(X),nl, fail.
displaySolCol(_).

&idea general.
% el predicado edge nos dice que vertices no DEBEN tener el mismo color.
% la idea es de la lista de varibales, se le asignan entre 1 y K numeros (colores),
%cada numero es un color, hemos de mirar que haya una combinacion en la que
%vertices vecinos no tengan el mismo color (mismo numero).


distinctColors(Vars):- edge(X,Y),write(X),write(' '),write(Y),fail.




color(K):-
    nVertices(N),
    length(Vars,N),
    Vars ins 1..K,   
    distinctColors(Vars),% adjacent vertices receive different values (to be implemented)
    label(Vars),!,
    displaySolCol(Vars).

