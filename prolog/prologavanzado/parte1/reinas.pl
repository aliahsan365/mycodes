threat(X,Prof,[C|_]):- X is C+Prof; X is C-Prof; X = C.
threat(X,Prof,[_|R]):- ProfMas1 is Prof + 1, threat(X,ProfMas1,R).
threat(_,[]):- fail.
threat(X,Y):- threat(X,1,Y).

configgen(0,[]).
configgen(X,[X|R]):- XMenos1 is X - 1, XMenos1 >= 0, configgen(XMenos1,R).


permute([], []).
permute([X|Rest], L) :-	permute(Rest, L1), select(X, L, L1).

goodconfig([]).
goodconfig([C|R]):- not(threat(C,R)), goodconfig(R).


nreinas(N,A):- configgen(N,Tab), permute(Tab,A),goodconfig(A),!.

%DispalySol.
writeSol(S,N):- between(1,N,I),nth1(E,S,I), writeFila(E,N),nl,fail.
writeSol(_,_).

writeFila(E,N):-between(1,N,I),writexop(I,E),fail.
writeFila(_,_).

writexop(I,I):- write('x '),!.
writexop(_,_):- write('. ').




reinas(N):- nreinas(N,Sol),writeSol(Sol,N),!.
reinas(_).
