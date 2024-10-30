%a.
%numara(E:intreg, L:lista, N:intreg)
%model de flux:
%numara(i,i,o) sau numara(i,i,i)
%E: elem ale carei aparitii le numaram in L
%L: lista in care numaram aparitiile lui E
%N: nr aparitiilor lui E in L

numara(_, [], 0).
numara(E, [H|T], N):-E=H,numara(E,T,N1),N is N1+1.
numara(E, [_|T], N):-numara(E,T,N).

%tranforma_multime(L:lista, R:multime)
%model de flux:
%transforma_multime(i,o)
%L: lista care trebuie transformata in multime
%R: multimea formata din lista L

transforma_multime([],[]).
transforma_multime([H|T], R):-numara(H,T,N),N>=1,!,transforma_multime(T,R).
transforma_multime([H|T], [H|R]):-numara(H,T,N),N=0,transforma_multime(T,R).

%b.
%cmmdc(Nr1:intreg, Nr2:intreg, R:intreg)
%model flux:
%cmmdc(i,i,o)
%Nr1: primul numar
%Nr2: al doilea numar
%R: cmmdc de Nr1 si Nr2

cmmdc(Nr1,Nr2,Nr1):-Nr2 is 0,!.
cmmdc(Nr1,Nr2,R):-E is mod(Nr1,Nr2),cmmdc(Nr2,E,R).

%ccmmdc(L:lista, R:intreg).
%model de flux:
%ccmmdc(i,o)
%L: lista de numere
%R: cmmdc-ul numerelor din lista L

ccmmdc([R],R):-!.
ccmmdc([H1|T],R):-ccmmdc(T,R1),cmmdc(H1,R1,R).
