% Ilie Petre-Cristian, Grupa 233, Numar 1

% cate_rasp_corecte(ListaRaspunsuriCorecte,ListaRaspunsuriStudenti,Nume,N)

% In prima faza doresc sa aflu lista cu raspunsurile studentului aferent
cate_rasp_corecte(LRC,[(ST,LRS)|_],ST,N) :- rasp_corecte(LRC,LRS,N). % Daca fac rost de ea, trimit sa compare listele de raspunsuri 
cate_rasp_corecte(LRC,[_|T],ST,N) :- cate_rasp_corecte(LRC,T,ST,N). % Daca nu este cel curent, ma uit in continuare in lista cu raspunsurile studentilor

rasp_corecte([],[],0).
% In cazul in care listele nu sunt de dimensiuni egale, va fi returnat false

rasp_corecte([H1|T1],[H1|T2],N) :- rasp_corecte(T1,T2,N1), N is N1 + 1. 
% Daca raspunsul curent al studentului coincide cu cel corect, ne uitam si la celelalte si la final adaugam 1 la total
rasp_corecte([_|T1],[_|T2],N) :- rasp_corecte(T1,T2,N).  % Altfel, doar trecem mai departe 

% Ex. verificari: cate_rasp_corecte([a,b,c,d],[(a,[a,b,c,c]),(b,[a,c,b,d]),(c,[a,a,b,c,d]),(d,[a,b])], a, N). unde inlocuim a cu studentul dorit.

