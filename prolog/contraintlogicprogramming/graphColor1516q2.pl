:- use_module(library(clpfd)).

numVertices(5).
edges([1-2,1-3,2-3,2-4,2-5,3-5]).
numColors(3).

listOfNPrologVars(0,[]).
listOfNPrologVars(N,[_|CasiVars]):- N1 is N-1, listOfNPrologVars(N1,CasiVars).


makeConstraints(_,[]).
makeConstraints(Vars,[X-Y|CasiEdges]):- nth1(X,Vars,C1),nth1(Y,Vars,C2), C1#\=C2,makeConstraints(Vars,CasiEdges). 


color:-numVertices(N),
	   edges(Edges),
	   listOfNPrologVars(N,Vars),
	   numColors(K),
	   Vars ins 1..K,
	   makeConstraints(Vars,Edges),
	   label(Vars),
	   write(Vars),
	   nl,!.
		
