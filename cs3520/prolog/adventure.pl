/*descriptions*/
description(valley, 'You are in a pleasent valley,with a trail ahead.').
description(path,'You are on a path, with ravines on both sides').
description(cliff,'You are teetering on the edge of a cliff').
description(fork,'You are at a fork in the path').
description(maze(_),'You are in a maze of twisty trails that are all alike').
description(mountaintop,'You are high on a mountaintop').

/*report*/
report:-
	at(you,X),
	description(X,Y),
	write(Y),
	nl.

/*map*/
connect(valley,up,path).
connect(path,right,cliff).
connect(path,left,cliff).
connect(path,up,fork).
connect(fork,left,maze(0)).
connect(fork,right,mountaintop).
connect(maze(0),left,maze(1)).
connect(maze(0),right,maze(3)).
connect(maze(1),left,maze(0)).
connect(maze(1),right,maze(2)).
connect(maze(2),left,fork).
connect(maze(2),right,maze(0)).
connect(maze(3),left,maze(0)).
connect(maze(3),right,maze(3)).

connect(_,start,valley).

connect(path,back,valley).
connect(fork,back,path).
connect(maze(0),back,fork).
connect(mountaintop,back,fork).
connect(maze(1),back,maze(0)).
connect(maze(3),back,maze(0)).
connect(maze(2),back,maze(1)).

/*move*/
move(Dir):-
	at(you,Loc),
	connect(Loc,Dir,Next),
	retract(at(you,Loc)),
	assert(at(you,Next)),
	report,
	!.
	
move(_):-
	write('Illeagal move\n'),
	report.
	
up:-move(up).
left:-move(left).
right:-move(right).
back:-move(back).
start:-move(start).

/*ogre*/
ogre:-
	at(ogre,Loc),
	at(you,Loc),
	write('The ogre takes out you liver bones.\n'),
	write('You die a terrible terrible death.\n'),
	retract(at(you,Loc)),
	assert(at(you,done)),
	!.
	
ogre.

treasure:-
	at(treasure,Loc),
	at(you,loc),
	write('Theres gold in them there hills.\n'),
	retract(at(you,Loc)),
	assert(at(you,done)),
	!.
	
treasure.

cliff:-
	at(you,cliff),
	write('You go splat now.\n'),
	retract(at(you,cliff)),
	assert(at(you,done)),
	!.
	
cliff.
/*
dennis:-
	rando(valley,0),
	rando(path,1),
	rando(fork,2),
	rando(mountaintop,3),
	rando(maze(1),4),
	rando(maze(2),5),
	rando(maze(3),6),
	is(Ran,6),
	rando(X,Ran),
	write(X).
*/
quiter:-
	write('You quiter'),
	!.
	
main:-
	at(you,done),
	write('Thank you come again.\n'),
	!.
	
main:-
	write('\nNext move --'),
	read(Move),
	call(Move),
	ogre,
	treasure,
	cliff,
	main.

go:-
	retractall(at(_,_)),
	assert(at(you,valley)),
	assert(at(ogre,maze(3))),
	assert(at(treasure,mountaintop)),
	write('Its adventure time!\n'),
	write('Legal moves are left, right, up, and back.\n'),
	write('or start to restart.\n'),
	write('End each move with a perriod.\n\n'),
	report,
	main.

	

