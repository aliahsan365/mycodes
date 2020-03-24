:- use_module(library(clpfd)).

ejemplo(0,   26, [1,2,5,10] ).  % Solution: [1,0,1,2]
ejemplo(1,  361, [1,2,5,13,17,35,157]).

%generamos la expresion vars*coins (pescalar)
mypescalar([],[],0).
mypescalar([X|L1],[Y|L2],E):- mypescalar(L1,L2,SE), E = (X*Y)+SE,!.


%hacemos la suma en forma de expresion
sumaE([],0).
sumaE([X|LE], S):- sumaE(LE,S1),S = S1+X.



main:- 
    ejemplo(1,Amount,Coins),
    nl, write('Paying amount '), write(Amount), write(' using the minimal number of coins of values '),
    write(Coins), nl,nl,
    length(Coins,N), 
    length(Vars,N), % get list of N prolog vars    
	Vars ins 0..Amount,
	mypescalar(Vars,Coins,E),
	E #= Amount,
	sumaE(Vars,S),
	%el solver lo lanza labeling para ir dando los valores.
	%primera parte es una lista que contiene la expresion a optimizar (heuristica)
	%la segunda lista, es donde el solver instancia los valores. Vendria a ser el Model de enconding.
	labeling([min(S)],Vars),	
	nl, write(Vars), nl,nl, halt.


 
