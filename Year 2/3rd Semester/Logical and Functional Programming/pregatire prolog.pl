
%pb1 P1

%cautareElement(l1..l2, x)
%1. fals, n=0
%2. true, x = l1
%3. cautareElement(l2..ln,x), altfel

cautareElement([],_):-false,!.
cautareElement([X|_],X):-true,!.
cautareElement([_|T],X):-cautareElement(T,X).


%diferenta(l1..ln, s1..sm)
%1. [], n=0
%2. l1..ln, m=0
%4. l1 (+) diferenta(l2..ln, s1..sn), altfel
%3. diferenta(l2..ln,s1..sn), cautareElement(s1..sn,l1) = adevarat

diferenta([],_,[]):-!.
%diferenta([],[],[]):-!.
diferenta([H|T],S,R):-cautareElement(S,H),!,diferenta(T,S,R).
diferenta([H|T],S,[H|R]):-diferenta(T,S,R).

%adaugare1(l1..ln)
%1. [], n=0
%2. l1 (+) 1 (+) adaugare(l2..ln), l1%2=0
%3. l1 (+) adaugare(l2..ln), altfel

adaugare1([],[]).
adaugare1([H|T],[H,1|R]):-H mod 2 =:= 0,!,adaugare1(T,R).
adaugare1([H|T],[H|R]):-adaugare1(T,R).


%nr prim


%prim(N: i, I:integer, P:integer)


prim(N, I,P):-I * I> N, !,P = 1.
prim(N,I,P):-N mod I =:=0,!,P = 0.
prim(N,I,P):-I2 is I+1, prim(N,I2,P).
isPrim(N):-N>1, prim(N,2,1).
