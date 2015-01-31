/*M=mother,F=father,C=child,S=sister,Sib=sibling,D=decendent,A=ancestor*/

mother(M,C).

father(F,C).

sister(S,Sib):-
    mother(M,S),
    father(F,S),
    mother(M,Sib),
    father(F,Sib).

grandson(Gs,Gp):-
    father(Gp,F),
    father(F,Gs).
    
firstcousin(C1,C2):-
    grandson(C1,Gp),
    grandson(C2,Gp),
    father(F1,C1),
    father(F2,C2),
    mother(M1,C1),
    mother(M2,C2).

decendent(D,A):-
    father(A,D).

decendent(D,A):-
    mother(A,D).

decendent(D,A):-
    father(F,D),
    decendent(A,F).

decendent(D,A):-
    mother(M,D),
    decendent(A,M).

famtest :-
    mother(Marg, Lisa),
    mother(Marg, Bart),
    mother(Marg, Maggie),
    father(Homer, Lisa),
    father(Homer, Bart),
    father(Homer, Maggie),
    father(Abe, Homer),
    mother(Mona, Homer),
    grandson(Bart, Abe),
    firstcousin(Bart, Cousin),
    firstcousin(Lisa, Cousin),
    firstcousin(Maggie, Cousin),
    decendent(Bart, Homer),
    decendent(Bart, Marg),
    decendent(Bart, Abe),
    decendent(Bart, Mona).
    
