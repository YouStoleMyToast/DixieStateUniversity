change(e,w).
change(w,e).

move([X,X,M3,C1,C2,C3],M1,M2,[Y,Y,M3,C1,C2,C3]):-
	change(X,Y).
	
move([M1,X,X,C1,C2,C3],M2,M3,[M1,Y,Y,C1,C2,C3]):-
	change(X,Y).
	
move([M1,M2,X,X,C2,C3],M3,C1,[M1,M2,Y,Y,C2,C3]):-
	change(X,Y).
	
move([M1,M2,M3,X,X,C3],C1,C2,[M1,M2,M3,Y,Y,C3]):-
	change(X,Y).

move([M1,M2,M3,C1,X,X],C2,C3,[M1,M2,M3,C1,Y,Y]):-
	change(X,Y).

move([X,M2,M3,C1,C2,C3],M1,nothing,[Y,M2,M3,C1,C2,C3]):-
	change(X,Y).

move([M1,X,M3,C1,C2,C3],M2,nothing,[M1,Y,M3,C1,C2,C3]):-
	change(X,Y).

move([M1,M2,X,C1,C2,C3],M3,nothing,[M1,M2,Y,C1,C2,C3]):-
	change(X,Y).

move([M1,M2,M3,X,C2,C3],C1,nothing,[M1,M2,M3,Y,C2,C3]):-
	change(X,Y).
	
move([M1,M2,M3,C1,X,C3],C2,nothing,[M1,M2,M3,C1,Y,C3]):-
	change(X,Y).

move([M1,M2,M3,C1,C2,X],C3,nothing,[M1,M2,M3,C1,C2,Y]):-
	change(X,Y).

%none
oneEq(X,X,X,X,X,X).
%none and one
oneEq(X,X,X,X,X,_).
oneEq(X,X,X,X,_,X).
oneEq(X,X,X,_,X,X).
%none and two
oneEq(X,X,X,X,_,_).
oneEq(X,X,X,_,_,X).
oneEq(X,X,X,_,X,_).
%none and three
oneEq(X,X,X,_,_,_).
%one and one
oneEq(X,X,_,X,X,_).
oneEq(X,X,_,X,_,X).
oneEq(X,X,_,_,X,X).
oneEq(X,_,X,X,X,_).
oneEq(X,_,X,X,_,X).
oneEq(X,_,X,_,X,X).
oneEq(_,X,X,X,X,_).
oneEq(_,X,X,X,_,X).
oneEq(_,X,X,_,X,X).
%one and two
oneEq(X,X,_,X,_,_).
oneEq(X,X,_,_,_,X).
oneEq(X,X,_,_,X,_).
oneEq(X,_,X,X,_,_).
oneEq(X,_,X,_,_,X).
oneEq(X,_,X,_,X,_).
oneEq(_,X,X,X,_,_).
oneEq(_,X,X,_,_,X).
oneEq(_,X,X,_,X,_).
%one and three
oneEq(X,X,_,_,_,_).
oneEq(X,_,X,_,_,_).
oneEq(_,X,X,_,_,_).
%two and two
oneEq(X,_,_,X,_,_).
oneEq(X,_,_,_,_,X).
oneEq(X,_,_,_,X,_).
oneEq(_,_,X,X,_,_).
oneEq(_,_,X,_,_,X).
oneEq(_,_,X,_,X,_).
oneEq(_,X,_,X,_,_).
oneEq(_,X,_,_,_,X).
oneEq(_,X,_,_,X,_).
%two and three
oneEq(X,_,_,_,_,_).
oneEq(_,X,_,_,_,_).
oneEq(_,_,X,_,_,_).
%three and three
oneEq(_,_,_,_,_,_).


safe([M1,M2,M3,C1,C2,C3]):-
	oneEq(M1,M2,M3,C1,C2,C3),
	
	oneEq(M1,M2,M3,C1,C2,_),
	oneEq(M1,M2,M3,C1,_,C3),
	oneEq(M1,M2,M3,_,C2,C3),
	oneEq(M1,M2,M3,C1,_,_),
	oneEq(M1,M2,M3,_,_,C3),
	oneEq(M1,M2,M3,_,C2,_),
	oneEq(M1,M2,M3,_,_,_),
	
	oneEq(M1,M2,_,C1,C2,_),
	oneEq(M1,M2,_,C1,_,C3),
	oneEq(M1,M2,_,_,C2,C3),
	oneEq(M1,M2,_,C1,_,_),
	oneEq(M1,M2,_,_,_,C3),
	oneEq(M1,M2,_,_,C2,_),
	oneEq(M1,M2,_,_,_,_),

	oneEq(M1,_,M3,C1,_,C3),
	oneEq(M1,_,M3,_,C2,C3),
	oneEq(M1,_,M3,C1,_,_),
	oneEq(M1,_,M3,_,_,C3),
	oneEq(M1,_,M3,_,C2,_),
	oneEq(M1,_,M3,_,_,_),
	
	oneEq(_,M2,M3,C1,_,C3),
	oneEq(_,M2,M3,_,C2,C3),
	oneEq(_,M2,M3,C1,_,_),
	oneEq(_,M2,M3,_,_,C3),
	oneEq(_,M2,M3,_,C2,_),
	oneEq(_,M2,M3,_,_,_),
	
	oneEq(M1,_,_,C1,_,_),
	oneEq(_,M2,_,C1,_,_),
	oneEq(_,_,M3,C1,_,_),
	oneEq(M1,_,_,_,C2,_),
	oneEq(_,M2,_,_,C2,_),
	oneEq(_,_,M3,_,C2,_),
	oneEq(M1,_,_,_,_,C3),
	oneEq(_,M2,_,_,_,C3),
	oneEq(_,_,M3,_,_,C3),
	oneEq(_,_,_,_,_,_).
	
solution([e,e,e,e,e,e],[]).
solution(Config,[Move|Rest]):-
	move(Config,Move,Move,NextConfig),
	safe(NextConfig),
	solution(NextConfig,Rest).
	
	
	
