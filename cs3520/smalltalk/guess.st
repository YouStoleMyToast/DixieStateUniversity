"smalltalk warmups"

"number guess"

Transcript show: ('Pick a number between 1 and 1000 and I will try to guess it in no more than 10 tries. After each guess, enter 0 if I got it right, -1 if I need to guess lower, and 1 if I need to guess higher.'); cr.

| high | high := 1000.
| low | low := 1.
| tries | tries := 1.
| guess | guess := (((high-low)//2)+low).
| response |

[ (high>low) & (tries <= 10) ] whileTrue: [
	guess := (((high-low)//2)+low).
	tries := tries+1.
	guessStr := guess storeString.
	triesStr := tries storeString.
	
	Transcript show: ('My guess is ', guessStr,'. Please enter -1, 0 or 1: '); cr.
	response := stdin nextLine asInteger.
	
	(response==-1) ifTrue: [high := guess - 1].
	(response==1) ifTrue: [ low := guess + 1 ].
	guess := (((high-low)//2)+low).
	guessStr := guess storeString.
	triesStr := tries storeString.
	
	(response==0) ifTrue: [ high := guess ].
	(response==0) ifTrue: [ low := guess ].
	(high==low) ifTrue: [ Transcript show: ('Your number is: ', guessStr,' and that took: ', triesStr,' tries!'); cr. tries=12.].
	(tries==10 and: [ high~=low ]) ifTrue: [ Transcript show: ('I have failed, I have brought shame upon me and my ancestors'); cr. tries=12.].
	
].


