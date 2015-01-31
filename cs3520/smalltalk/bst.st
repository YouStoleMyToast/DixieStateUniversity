"smalltalk warmups"

"bst"

Object subclass: Node [ :inkey |
	| key | key := inkey.
	| left | left := nil.
	| right | right := nil.
	| newnode | newnode := nil.
	
	insert:[
		
		
	]
	
	"use nil to represent leaf nodes - doesn't require defining of new type"
	"insert method - returns new node that has been updated- This may be a completely new Node, or it may be the existing node with modifications made."
	

]

Object subclass: Tree [
	
	| typeinput |
	| valueinput |
	| tree | := Node new 
	
	"is a container for the tree that responds to user messages"
	"initially has a single nodeobject"
	
	set: key to: value [
	
	]
	
	get: key [
	
	]
	
	Transcript show: ("type g for get or s for set"); cr.
	typeinput := stdin nextLine
	
	(typeinput==g) ifTrue: [
		Transcript show: ("Value to get?"); cr.
		valueinput := stdin nextLine.
		
		
		
		(valueinput==nil) ifTrue: [ Transcript show: ("Value is not in tree"); cr.]
		(valueinput==nil) ifFalse: [ Transcript show: ("Value is in tree"); cr.]
		].
		
	(typeinput==s) ifTrue: [
		Transcript show: ("Value to set?"); cr.
		valueinput := stdin nextLine.
		
		Transcript show: (valueinput, " is now in the tree"); cr.]
		].
	
	
	
]










