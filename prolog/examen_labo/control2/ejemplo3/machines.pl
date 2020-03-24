symbolicOutput(0). % set to 1 to see symbolic output only; 0 otherwise.


%% Complete the ... in order to solve the following problem.
%% We want to do the weekly production planning for a factory that
%% produces plastic pieces for cars.  It has a number of tasks (each
%% task is to produce a lot of identical pieces).  Each task has to be
%% done on a machine, and machines cannot handle more than one task
%% simultaneously. We have a number of available hours to complete all
%% tasks, but we want to finish all tasks as soon as possible.

%% NEW FOR THIS EXAM: the duration of each task depends on the machine used!
%% Do NOT modify the following input example (2000 variables and 50.000 clauses suffice).
%% Do NOT change names of predicates, and upload this file with this name: machines.pl


numMachines(6).
availableHours(70).
task(  1,  2,55, [1-6,5-19,6-10]). %task 1 on machine 1 takes 6h, on machine 5 it takes 19h, etc.
task(  2,  8,54, [4-10,6-8]).
task(  3, 10,64, [1-22,5-11]).
task(  4,  2,51, [1-19,5-18]).
task(  5, 11,69, [4-16,6-6]).
task(  6, 11,52, [4-18,6-20]).
task(  7,  4,48, [1-15,4-10]).
task(  8,  3,43, [3-18,4-22,6-16]).
task(  9,  8,40, [2-15,5-12]).
task( 10, 14,58, [4-6,5-9]).
task( 11, 10,57, [2-23,3-18,4-10]).
task( 12,  8,45, [3-10,4-5,5-11]).
task( 13,  9,64, [5-23,6-8]).
task( 14, 13,60, [2-15,3-14,6-11]).
task( 15, 12,53, [1-18,2-13,3-15]).
task( 16,  7,51, [2-18,3-22,6-23]).
task( 17,  2,63, [1-18,4-20]).
task( 18, 14,49, [4-6,6-18]).
task( 19,  5,66, [1-21,2-10,4-14]).
task( 20, 14,43, [2-6,4-14,6-12]).


%%%%%% Take your time to UNDERSTAND and USE these helpful definitions:

task(T):-              task(T,_,_,_).
earliestStart(T,E):-   task(T,E,_,_).
latestFinish(T,L):-    task(T,_,L,_).
usableMachine(T,M):-   task(T,_,_,L), member( M-_, L ).
duration(T,M,D):-      task(T,_,_,L), member( M-D, L ).
machine(M):-           numMachines(N), between(1,N,M).

possiblyActive( T, AvailableHours, H ):-  % task T might be active on hour H:
    earliestStart(T, EarliestStart),
    latestFinish( T, LatestFinishTask),
    LatestFinish is min(AvailableHours,LatestFinishTask),
    between(EarliestStart,LatestFinish,H).

possibleStart( T, AvailableHours, H ):-  % task T might start on hour H:
    earliestStart(T, EarliestStart),
    between(EarliestStart,AvailableHours,H),
    existsFastEnoughMachineForThisStartTime(T,AvailableHours,H).

existsFastEnoughMachineForThisStartTime(T,AvailableHours,H):-
    usableMachine(T,M),
    machineIsFastEnoughForThisStartTime(T,M,AvailableHours,H),!.

machineIsFastEnoughForThisStartTime(T,M,AvailableHours,H):-
    latestFinish(T,LatestFinish),
    duration(T,M,D),
    H+D-1 =< min(AvailableHours,LatestFinish), !.



% MANDATORY: use the following types of symbolic propositional variables (you CANNOT add more):
%   1. start-T-H    means:  "task T starts at hour H"
%   2. machine-T-M  means:  "task T uses machine M"
%   3. active-T-H   means:  "task T is active at hour H"


writeClauses(AvailableHours):- 
    eachTaskStartsOnce(AvailableHours),
    eachTaskOneMachine,
    noTaskStartsTooLate(AvailableHours),
    relateStartVarsWithActiveVars(AvailableHours),
    noTwoTasksSimulteanouslyOnSameMachine(AvailableHours),
    true,!.


eachTaskStartsOnce(AvailableHours):-
    task(T), findall( start-T-H, possibleStart(T,AvailableHours,H), Lits ), exactly(1,Lits), fail.
eachTaskStartsOnce(_).

eachTaskOneMachine:-
    task(T), findall( machine-T-M, usableMachine(T,M), Lits ),  exactly(1,Lits), fail.
eachTaskOneMachine.

% clauses eliminating forbidden combinations of machines and starts:
noTaskStartsTooLate(AvailableHours):- 
    possibleStart(T,AvailableHours,HStart),
    usableMachine(T,M),
    ...
    writeClause([ ... ]), fail.
noTaskStartsTooLate(_).

% clauses "if ... then active-T-H", where ... also depends on the machine:
relateStartVarsWithActiveVars(AvailableHours):- 
    possibleStart(T,AvailableHours,HStart),
    duration(T,M,D),
    ...
relateStartVarsWithActiveVars(_).


noTwoTasksSimulteanouslyOnSameMachine(AvailableHours):-
    task(T1), usableMachine(T1,M), possiblyActive( T1, AvailableHours, H ),
    task(T2), usableMachine(T2,M), possiblyActive( T2, AvailableHours, H ), T1<T2,
    writeClause([ \+active-T1-H, \+active-T2-H, \+machine-T1-M,  \+machine-T2-M ]), fail.  
noTwoTasksSimulteanouslyOnSameMachine(_).


% =====================================================================
%DisplaySol. Do not modify:
displaySol(_):-
    write('        10        20        30        40        50        60        70        80'), nl,
    write('12345678901234567890123456789012345678901234567890123456789012345678901234567890'), nl,fail.
displaySol(M):- machine(Mach), nl, write('machine '), write(Mach), write(':'), nl,  displayMachine(M,Mach), fail.
displaySol(_):- nl,nl,!.


displayMachine(M,Mach):-     availableHours(AH), between(1,AH,H),               writeX(H,M,Mach), fail.
displayMachine(M,Mach):- nl, availableHours(AH), between(1,AH,H), 0 is H mod 2, writeS(H,M,Mach), fail.
displayMachine(_,_):- nl.
    
writeX(H,M,Mach):- member(machine-T-Mach,M), member(start-T-S,M), duration(T,Mach,D), F is S+D-1, between(S,F,H),
		   X is T mod 10, write(X), !.
writeX(_,_,_):- write(' '),!. 

writeS(H,M,Mach):- member(machine-T-Mach,M), member(start-T-S,M), (H is S+3;H is S+2), writeNum2(T), !.
writeS(_,_,_):- write('  '),!. 

writeNum2(T):-T<10, write(' '), write(T), !.
writeNum2(T):-                  write(T), !.

%=====================================================

% This predicate computes the duration for each new solution, so we can look for better ones:
hoursUsed(M,K):- findall(H, member(active-_-H,M), L),    max_list(L,K),!.

%=====================================================

main:- symbolicOutput(1), !, availableHours(AH),
       initClauseGeneration, writeClauses(AH), halt.   % print the clauses in symbolic form and halt
main:- availableHours(AH), initClauseGeneration,
       tell(clauses), writeClauses(AH), told,     % generate the (numeric) SAT clauses and call the solver
       tell(header),  writeHeader,  told,
       numVars(N), numClauses(C), 
       write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
       shell('cat header clauses > infile.cnf',_),
       nl,nl,write('Looking for initial planning taking at most '), write(AH), write(' hours.'), nl,
       write('Launching picosat...'), nl,
       shell('picosat -v -o model infile.cnf', Result),  % if sat: Result=10; if unsat: Result=20.
       treatResult(Result,[]),!.

treatResult(10,_):- 
    see(model), symbolicModel(M), seen, hoursUsed(M,K),
    write('plan found that takes '), write(K), write(' hours '),nl,nl, K1 is K-1,
    displaySol(M),     initClauseGeneration,
    nl,nl,write('Now looking for even better plannings....'), nl,
    tell(clauses), writeClauses(K1), told,
    tell(header),  writeHeader,  told,
    numVars(N),numClauses(C),
    write('Generated '), write(C), write(' clauses over '), write(N), write(' variables. '),nl,
    shell('cat header clauses > infile.cnf',_),
    write('Launching picosat...'), nl,
    shell('picosat -v -o model infile.cnf', Result),  % if sat: Result=10; if unsat: Result=20.
    treatResult(Result,M),!.
treatResult(20,[]       ):- write('No solution exists.'), nl, halt.
treatResult(20,BestModel):- nl,nl,write('Optimal solution: '),nl, displaySol(BestModel), halt.

    
%===========================================================
initClauseGeneration:-  %initialize all info about variables and clauses:
    retractall(numClauses(   _)), 
    retractall(numVars(      _)), 
    retractall(varNumber(_,_,_)),
    assert(numClauses( 0 )), 
    assert(numVars(    0 )),     !.

writeClause([]):- symbolicOutput(1),!, nl.
writeClause([]):- countClause, write(0), nl.
writeClause([Lit|C]):- w(Lit), writeClause(C),!.
w( Lit ):- symbolicOutput(1), write(Lit), write(' '),!.
w(\+Var):- var2num(Var,N), write(-), write(N), write(' '),!.
w(  Var):- var2num(Var,N),           write(N), write(' '),!.

% given the symbolic variable V, find its variable number N in the SAT solver:
:-dynamic(varNumber/3).
var2num(V,N):- hash_term(V,Key), existsOrCreate(V,Key,N),!.
existsOrCreate(V,Key,N):- varNumber(Key,V,N),!.                            % V already existed with num N
existsOrCreate(V,Key,N):- newVarNumber(N), assert(varNumber(Key,V,N)), !.  % otherwise, introduce new N for V

writeHeader:- numVars(N),numClauses(C), write('p cnf '),write(N), write(' '),write(C),nl.

countClause:-     retract( numClauses(N0) ), N is N0+1, assert( numClauses(N) ),!.
newVarNumber(N):- retract( numVars(   N0) ), N is N0+1, assert(    numVars(N) ),!.
 
% Getting the symbolic model M from the output file:
symbolicModel(M):- get_code(Char), readWord(Char,W), symbolicModel(M1), addIfPositiveInt(W,M1,M),!.
symbolicModel([]).
addIfPositiveInt(W,L,[Var|L]):- W = [C|_], between(48,57,C), number_codes(N,W), N>0, varNumber(_,Var,N),!.
addIfPositiveInt(_,L,L).
readWord( 99,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ c
readWord(115,W):- repeat, get_code(Ch), member(Ch,[-1,10]), !, get_code(Ch1), readWord(Ch1,W),!. % skip line starting w/ s
readWord(-1,_):-!, fail. %end of file
readWord(C,[]):- member(C,[10,32]), !. % newline or white space marks end of word
readWord(Char,[Char|W]):- get_code(Char1), readWord(Char1,W), !.

%========================================================================================

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Everything below is given as a standard library, reusable for solving 
%    with SAT many different problems.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%% Cardinality constraints on arbitrary sets of literals Lits:
% For example the following generates the clauses expressing that 
%     exactly K literals of the list Lits are true:
exactly(K,Lits):- atLeast(K,Lits), atMost(K,Lits),!.

atMost(K,Lits):-   % l1+...+ln <= k:  in all subsets of size k+1, at least one is false:
    negateAll(Lits,NLits), 
    K1 is K+1,    subsetOfSize(K1,NLits,Clause), writeClause(Clause),fail.
atMost(_,_).

atLeast(K,Lits):-  % l1+...+ln >= k: in all subsets of size n-k+1, at least one is true:
    length(Lits,N),
    K1 is N-K+1,  subsetOfSize(K1, Lits,Clause), writeClause(Clause),fail.
atLeast(_,_).

negateAll( [], [] ).
negateAll( [Lit|Lits], [NLit|NLits] ):- negate(Lit,NLit), negateAll( Lits, NLits ),!.

negate(\+Lit,  Lit):-!.
negate(  Lit,\+Lit):-!.

subsetOfSize(0,_,[]):-!.
subsetOfSize(N,[X|L],[X|S]):- N1 is N-1, length(L,Leng), Leng>=N1, subsetOfSize(N1,L,S).
subsetOfSize(N,[_|L],   S ):-            length(L,Leng), Leng>=N,  subsetOfSize( N,L,S).

% Express that Var is equivalent to the disjunction of Lits:
expressOr( Var, Lits ):- member(Lit,Lits), negate(Lit,NLit), writeClause([ NLit, Var ]), fail.
expressOr( Var, Lits ):- negate(Var,NVar), writeClause([ NVar | Lits ]),!.

% Express that Var is equivalent to the conjunction of Lits:
expressAnd( Var, Lits ):- negate(Var,NVar), member(Lit,Lits),  writeClause([ NVar, Lit ]), fail.
expressAnd( Var, Lits ):- negateAll(Lits,NLits), writeClause([ Var | NLits ]),!.


