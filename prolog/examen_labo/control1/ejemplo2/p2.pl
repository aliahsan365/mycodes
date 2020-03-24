particion([],[],[]).  
particion([X|C],[X|S],R):-particion(C,S,R).
particion([X|C],S,[X|R]):-particion(C,S,R).

suma([],0).
suma([X|L],S) :- suma(L,S1), S is S1+X.

igual_particion(L,S1,S2):-
    particion(L,S1,S2),
    suma(S1,T),
    suma(S2,T).
