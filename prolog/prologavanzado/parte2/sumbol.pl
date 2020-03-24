primero([X|_],X).

ultimo(L,X):- reverse(L,LR), primero(LR,X).

eliminaPrimero([_|L],L).

programa([begin|P]):- 
	ultimo(P,end),
	reverse(P,PR),
    eliminaPrimero(PR,PIR),
    reverse(PIR,PI),
	instrucciones(PI),!.



instrucciones(L):- 
	instruccion(L).
instrucciones(L):- 
    append(L1,[;|L2],L),
    instruccion(L1),
    instrucciones(L2),!.



instruccion(L):-
    variable(X1),
    variable(X2),
    variable(X3),
    simbol(S),
    append([X1],[=, X2, S, X3], L).

instruccion([if|L]):-
    ultimo(L,endif),
    reverse(L,LR),
    eliminaPrimero(LR,LIR),
    reverse(LIR,LI),
    variable(X1),
    variable(X2),
    append([X1,=,X2,then], L1, LI),
    append(L2,[else|L3],L1),
    instrucciones(L2),
	instrucciones(L3).

variable(x).
variable(y).
variable(z).

simbol(+).

