% Ilie Petre-Cristian, Grupa 233, Numar 1

% P ::- start C
% C ::- stop | E ::: C
% E ::- mem | n | E+E | save E

% Precedenta operatori

:- op(100, xf, {}).
:- op(1100, yf, ;).

% Evaluare expresii

exp(I) :- integer(I). 
exp(X) :- atom(X).
exp(A1 + A2) :- exp(A1),exp(A2).
exp(mem = E) :- exp(E), atom(mem).

% Evaluare statementuri

stmt(stop).
stmt(St1;St2) :- stmt(St1), stmt(St2).
stmt({St}) :- stmt(St).

% Evaluare program

program(St,Exp) :-
	stmt(St),
	exp(Exp).


% ID - Obtinere / modificare valoare din memorie

get(S,X,I) :- member(vi(X,I),S).
get(_,_,0).

set(S,X,I,[vi(X,I)|S1]) :- del(S,X,S1).
del([vi(X,_)|S],X,S).
del([H|S],X,[H|S1]) :- del(S,X,S1) .
del([],_,[]).

smallstepA(X,S,I,S) :-
	atom(X),
	get(S,X,I).

% Add

smallstepA(E1+E2,S,E,S):-
	integer(E1), integer(E2),
	E is E1+E2.
% Asgn

smallstepS(MEM = E, S, skip, S1) :-
	integer(E), set(S,MEM,E,S1).

% Next Statement

smallstepS((skip;St2), S, St2, S).
smallstepS((St1;St),S1,(St2;St),S2) :-
smallstepS(St1,S1,St2,S2).

smallstepS({E}, S, E, S).

% Programe

smallstepP(skip, AE1, S1, skip, AE2, S2) :-
	smallstepA(AE1, S1, AE2, S2).
smallstepP(St1, AE, S1, St2, AE, S2) :-
	smallstepS(St1, S1, St2, S2).

run(skip, I, _, I).
run(St1, AE1, S1, I) :-
	smallstepP(St1, AE1, S1, St2, AE2, S2),
	run(St2, AE2, S2, []).

run_program(Name) :- defpg(Name, {P}, E),
	run(P, [(mem,0)|E], [], I), % Initial mem = 0 la orice program

defpg(pg1, {mem},[]).



