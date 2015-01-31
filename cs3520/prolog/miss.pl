miss(State):-
	State=[Me,Ce,Mb,Cb,Mw,Cw],
	write(State),write('\n'),
	Me is Me,Ce is Ce,Mb is Mb,Cb is Cb,Mw is Mw,Cw is Cw,
	
	/*East to boat*/
	Ce=Me->Ce2 is Ce-1 ->Cb2 is Cb+1 ->Cw2 is Cw
		 ->Me2 is Me-1 ->Mb2 is Mb+1 ->Mw2 is Mw,
	/*Ce>Me->Ce2 is Ce-2 ->Cb2 is Cb+2 ->Cw2 is Cw
		 ->Me2 is Me ->Mb2 is Mb ->Mw2 is Mw,*/
	
	/*Ce>Cb->Ce2 is Ce-1 ->Cb2 is Cb+1 ->Cw2 is Cw,
	Me>Mb->Me2 is Me-1 ->Mb2 is Mb+1 ->Mw2 is Mw,*/
	
	State2=[Me2,Ce2,Mb2,Cb2,Mw2,Cw2],
	write(State2),write('\n'),
	
	Me2>=Ce2->write('east alive\n'),
	/*Boat to West*/
	Cb2>0->Ce3 is Ce2 ->Cb3 is 0 ->Cw3 is Cb2+Cw2,
	Mb2>0->Me3 is Me2 ->Mb3 is 0 ->Mw3 is Mb2+Mw2,
	
	State3=[Me3,Ce3,Mb3,Cb3,Mw3,Cw3],
	write(State3),write('\n'),
	
	/*West to boat*/
	Cw3>0->Ce4 is Ce3 ->Cb4 is Cb3+1 ->Cw4 is Cw3-Cb4,
	Mw3>0->Me4 is Me3 ->Mb4 is Mb3+1 ->Mw4 is Mw3-Mb4,
	
	State4=[Me4,Ce4,Mb4,Cb4,Mw4,Cw4],
	write(State4),write('\n'),
	
	Mw4>=Cw4->write('west alive\n'),
	/*boat to east*/
	Cb4>0->Ce5 is Ce4+1 ->Cb5 is 0 ->Cw5 is Cb4+Cw4,
	Mb4>0->Me5 is Me4+1 ->Mb5 is 0 ->Mw5 is Mb4+Mw4,
	
	State5=[Me5,Ce5,Mb5,Cb5,Mw5,Cw5],
	write(State5),write('\n'),
	
	miss(State3).
	



