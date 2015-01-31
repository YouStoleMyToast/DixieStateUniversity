Object subclass: State [
	| startcount | startcount := 3.
	| missnear | missnear := 3.
	| cannnear | cannnear := 3.
	| boatnear | boatnear := true.
	| boatcap | boatcap := 2.
	| moves | moves := OrderedCollection new.
	
	isGoal [((missnear==0) & (cannnear==0)) ifTrue:[Transcript show:('You win');cr.].]
	isValid [((missnear between: 0 and: startcount) & (cannnear between: 0 and: startcount)) ifTrue: [^true].]
	isSafe [((missnear>=cannnear) | (missnear==0)) ifTrue:[^true].]
	oneMove [
	
		(boatnear==true) ifTrue: [
			boatnear := false.
			(missnear=missnear-2).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. missnear:=missnear+2].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear:=missnear+2].
			(cannnear:=cannnear-2).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. cannnear:=cannnear+2].
				((self isValid==false) | (self isSafe==false)) ifTrue: [cannnear:=cannnear+2].
			(missnear:=missnear-1).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. missnear:=missnear+1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear:=missnear+1].
			(cannnear:=cannnear-1).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. cannnear:=cannnear+1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [cannnear:=cannnear+1].
			(missnear:=missnear-1) and: [(cannnear:=cannnear-1)].
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add:{missnear. cannnear. boatnear}. missnear:=missnear+1. cannnear:=cannnear+1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear:=missnear+1. cannnear:=cannnear+1].
		].
		(boatnear==false) ifTrue: [
			boatnear := true.
			(missnear=missnear+2).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. missnear:=missnear-2].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear=missnear-2].
			(cannnear=cannnear+2).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear}. cannnear:=cannnear-2].
				((self isValid==false) | (self isSafe==false)) ifTrue: [cannnear:=cannnear-2].
			(missnear=missnear+1).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. missnear:=missnear-1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear:=missnear-1].
			(cannnear=cannnear+1).
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. cannnear:=cannnear-1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [cannnear:=cannnear-1].
			(missnear:=missnear+1) and: [(cannnear:=cannnear+1)].
				((self isValid==true) & (self isSafe==true)) ifTrue: [moves add: {missnear. cannnear. boatnear}. missnear:=missnear-1. cannnear:=cannnear-1].
				((self isValid==false) | (self isSafe==false)) ifTrue: [missnear:=missnear-1. cannnear:=cannnear-1].
		].
	].
]

Object subclass: Solver [
	s := State new.
	s oneMove.
	q:=s moves at: 1.
	printSolution [Transcript show: (q); cr.].
]

l := Solver new.
l printSolution.


















