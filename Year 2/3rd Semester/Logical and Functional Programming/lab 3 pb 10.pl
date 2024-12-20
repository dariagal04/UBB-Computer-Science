%submultime(L: lista, Sub: lista)
%model de flux (i,o)
%L: lista data ca input
%Sub: o submultime a listei date input

submultime([], []).
submultime([H|T], [H|Sub]) :-
    submultime(T, Sub).
submultime([_|T], Sub) :-
    submultime(T, Sub).



%suma(L: lista, S:suma)
%model de flux (i,o)
%L:lista data ca input
%S: suma elementelor din lista

suma([], 0).
suma([H|T], S) :-
    suma(T, ST),
    S is H + ST.



%submultimi_suma_divizibila(L: lista, N: integer, Sub: lista)
%model de flux (i,i,o)
%L: lista data input
%N: numar cu care trebuie sa fie divizibila suma elementelor din lista
% Sub: submultime in care suma elementelor din lista initiala este
% divizibila cu N

submultimi_suma_divizibila(L, N, Sub) :-
    submultime(L, Sub),
    Sub \= [],
    suma(Sub, S),
    S mod N =:= 0.

%                       __
%                      |   [], n=0
%submultime(l1..ln) =  |   l1 (+) submultime(l2..ln),
%                      |   submultime(l2..ln), altfel
%                       __
%
%
%                __
%               |   0, n=0
%suma(l1..ln) = |   suma(l2..ln)+l1
%                __
%
%                                         __
%                                        |   [], n=0
% submultimi_suma_divizibila(l1..ln,N) = | suma(submultime(l1..ln)) , n>0suma(submultime(l1..ln))%N=0
%                                         __
