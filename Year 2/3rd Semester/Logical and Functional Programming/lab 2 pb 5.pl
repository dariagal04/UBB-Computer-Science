
%pb5

% a) Sa se determine pozitiile elementului maxim dintr-o lista liniara.
% De ex: poz([10,14,12,13,14], L) va produce L = [2,5]. b) Se da o lista
% eterogena, formata din numere intregi si liste de numere intregi. Sa se
% inlocuiasca fiecare sublista cu pozitiile elementului maxim din
% sublista respectiva. De ex: [1, [2, 3], [4, 1, 4], 3, 6, [7, 10, 1, 3,
% 9], 5, [1, 1, 1], 7] => [1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7] a)
% calc_maxim(L: lista liniara, M: intreg, Maxim:intreg) model de flux
% (i,i,o) L: lista din care vrem sa aflam maximul M: variablia de cautare
% a maximului Maxim: maximul din lista

%calc_maxim([],M,M):-!.
%calc_maxim([H1,H2|T],M,Maxim):-H1>M, calc_maxim([H2|T],H1,Maxim).
%calc_maxim([H1,H2|T],M,Maxim):-H1=<M, calc_maxim([H2|T],M,Maxim).

calc_maxim([M], M).
calc_maxim([H|T], H):- calc_maxim(T, M), H>=M.
calc_maxim([H|T], M) :- calc_maxim(T, M), H<M.



%poz_cautat(L:lista liniara, P:intreg, M:intreg, C:lista, R:lista)
%model de flux (i,i,i,i,o)
%L: lista din care cautam pozitiile
%P: variablia pentru cautarea pozitiilor
%M: elementul caruia ii cautam pozitiile in lista
%C: lista acumulatoare in care se adauga pozitiile
%R: lista rezultat a cautarii pozitiilor

poz_cautat([],_,_,C,C).
poz_cautat([H|T],P,H,C,R):-P1 is P+1, poz_cautat(T,P1,H,[P|C],R).
poz_cautat([H|T],P,M,C,R):-M\=H,P1 is P+1, poz_cautat(T,P1,M,C,R).




%poz_maxim(L: lista liniara, Rez: lista)
%model de flux (i,o)
%L: lista din care cautam pozitiile elementului maxim
%Rez: lista rezultat cu pozitiile elementului maxim

poz_maxim([],[]).
poz_maxim([H|T],Rez):-calc_maxim([H|T],M),poz_cautat([H|T],1,M,[],Rez).



%b)
%inloc_sublista(L:lista eterogena, Rez: lista eterogena)
%model de flux (i,o)
%L: lista eterogena de modificat
%Rez: lista rezultata in urma modificarii

inloc_sublista([],[]).
inloc_sublista([H|T],[P|Rez]):-is_list(H),!,poz_maxim(H,P),inloc_sublista(T,Rez).
inloc_sublista([H|T],[H|Rez]):-inloc_sublista(T,Rez).
%                       __
%                      |  1. fals,   n=0
%                      |  2. l1,     n = 1
%calc_maxim(l1..ln)=   |  3. calc_maxim(l2..ln, l1) , n>1 si l1>M
%                      |  4. calc_maxim(l2..ln, M), n>1 si l1≤ M
%                       __
%
%                          __
%                         |  1. lista vida, n=0
%poz_cautat(l1..ln, P, M)=|  2. P (+) poz_cautat(l2..ln, P+1,l1),n≥1 sil1=M
%                         |  3. poz_cautat(l2..ln, P+1,M), n≥1 si l1≠M
%                          __
%
%                       __
%                      |  1. lista vida, n=0
%poz_maxim( l1..ln ) = | 2. poz_cautat(l1..ln, 1, calc_maxim(l1..ln,-1))
%                       __
%
%
%                        __
%                       |  1. lista vida, n=0
%inloc_sublista(l1..ln)=| 2. poz_maxim(l1) (+) inloc_sublista(l2..ln),l1 e lista si n≥1
%                       | 3. l1 (+) inloc_sublista(l2..ln) , l1 nu e lista si n≥1
%                        __
