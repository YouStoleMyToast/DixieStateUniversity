mac(M,C):-
	write('mac: '),
	out(M,C),
	move(M,C).
	
move(M,C):-
	write('move1: '),
	out(M,C),
	M is M-2,
	safe(M,C).
move(M,C):-
	write('move2: '),
	out(M,C),
	C is C-2,
	safe(M,C).
move(M,C):-
	write('move3: '),
	out(M,C),
	M is M-1,
	C is C-1,
	safe(M,C).

safe(M,C):-
	write('safe: '),
	M>C,
	M>=0,
	C>=0,
	out(M,C),
	back(M,C).

back(M,C):-
	write('back1: '),
	C is C+1,
	out(M,C).
back(M,C):-
	write('back2: '),
	M is M+1,
	out(M,C).
back(M,C):-
	write('back3: '),
	M is M+1,
	C is C+1,
	out(M,C).	
	
out(M,C):-
	write('\n'),
	write('M: '),write(M),
	write('C: '),write(C).
	
	
	
	
