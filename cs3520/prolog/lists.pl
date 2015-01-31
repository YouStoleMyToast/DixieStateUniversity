third(L,T):-
	[_,_,T|_]=L.

del3(L,T):-
	L=R,
	L=S,
	L=P,
	[G|_]=P,
	[_,D|_]=S,
	[_,_,_|E]=R,
	[G,D,E]=T.

evensize(L):-
	[_,_|T]=L,
	evensize(T),!.
evensize([]).

isduped(L):-
	[A,B|T]=L,
	A=B,
	isduped(T),!.
isduped([]).


thirdtest:-
    third([1,2,3],T),
    third([1,2,3,4],T),
    third([1,2,3,4,5],T).
    
deltest:-
	del3([1,2,3],T),
    del3([1,2,3,4],T),
    del3([1,2,3,4,5],T).

dupetest:-
	isduped([1,1]),
	isduped([1,1,2,2]),
	isduped([1,1,2,2,3,3,4,4,5,5]),
	not(isduped([1,1,2,3])),
	not(isduped([1,1,2,2,3,3,4,4,5,6])).

eventest:-
	evensize([]),
	not(evensize([1])),
	evensize([1,2]),
	evensize([1,2,3,4]),
	not(evensize([1,2,3,4,5,6,7,8,9])).
