:- use_module(library(clpfd)).
    
% Complete the following program to generalize the well-known puzzle SEND+MORE=MONEY: assign distinct
% digits in 0..9 to each letter such that the sum is correct, e.g.,  2817+0368=03185.
% For instance we want to do LI+IS+NICE=TRUE.
% Do not change names of predicates, and upload this file with this name "sums.pl".

main:- puzzle2( [S,E,N,D] + [M,O,R,E]     = [M,O,N,E,Y] ), halt.  %puzzle2 is for two summands
main:- puzzle3( [L,I] + [I,S] + [N,I,C,E] = [T,R,U,E]   ), halt.
main:- write('no solution'), nl,nl, halt.

puzzle2(L1+L2=R):-
    append( L1, L2, L12),
    append( ... , ... , L), sort(L,Vars),  %sort eliminates repetitions
    Vars ins ...
    all_different(Vars),
    makeSum(L1,S1),
    ...
    ... + ... #= ...,
    ...
    write(L1+L2=R), nl,nl,!.

puzzle3(L1+L2+L3=R):-
    ...
    write(L1+L2+L3=R), nl,nl,!.


makeSum(L,S):- reverse(L,L1), makeSum1(1,L1,S),!. % e.g., makeSum(  [A,B,C],  1*C + 10*B + 100*A ).

makeSum1(  F , [S] ,   ...    ):-!.
makeSum1(... , ... , F*S + S1 ):- ...

