:- use_module(library(clpfd)).

%input(WeightList,PricesList,TotalWeight)
input1([1,2,3,5,6,7],[1,4,7,11,14,15],80).
input2([1,1,1],[80,1,1],80).
input3([80,1,1],[80,1,1],80).
input4([80,1,1],[0,0,1],80).

pescalar([],[],0).
pescalar([X|L1],[Y|L2],S):- pescalar(L1,L2,S1),S = S1+(X*Y).

china:- input4(Weights,Prices,Total),
		length(Weights,K),
	    length(L,K),
	    L ins 0..Total,
		pescalar(Weights,L,Exp1),
		Exp1 #=< Total,
		L2 = L,
		pescalar(Prices,L2,Exp2),
		labeling([max(Exp2)],L),
		write(L),
		nl,!.
		
		
	

