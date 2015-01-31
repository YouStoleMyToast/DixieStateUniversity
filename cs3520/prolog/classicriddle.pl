%classic riddle of man(m), wolf(d), goat(g), cabbage(c), man can also go accross with nothing(n)

change(e,w).
change(w,e).

move([x,x,g,c],w,[y,y,g,c]):-
	change(x,y).

move([x,d,x,c],g,[y,d,y,c]):-
	change(x,y).

move([x,d,g,x],c,[y,d,g,y]):-
	change(x,y).

move([x,d,g,c],n,[y,d,g,c]):-
	change(x,y).
	
oneEq(x,x,v).
oneEq(x,q,x).

safe([m,d,g,c]):-
	oneEq(m,g,d),
	oneEq(m,g,c).

solution([e,e,e,e],[]).

solution(config,[fmove|rest]):-
	move(config,fmove,nextconfig),
	safe(nextconfig),
	solution(nextconfig,rest).

%length(x,7),solution([w,w,w,w],x).
%x=[g,n,d,g,c,n,g]
