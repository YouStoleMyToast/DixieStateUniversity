import random

def roll_die(sides):
	x = random.randrange(1,sides+1)
	return x

def take_turn(player):
	turn_points

def callback(eventints = 0):
	keep_rolling = 1
	print
	print "Player",player,"it is your turn."
	raw_input("Press enter")
	while keep_rolling == 1:
		roll = roll_die(6)
		print
		print "You rolled a",roll
		print
		if roll == 1:
			turn_points = 0
			keep_rolling = 0
		else:
			turn_points = turn_points + roll
			print turn_points
			print
			print "Do you want to roll again? 1=Yes 2=No"
			Y = input()
			if Y == 1:
				keep_rolling = 1
			else:
				keep_rolling = 0

	print "Your turn is over"
	return turn_points

def show_instructions():
	print "Press enter to roll the die."
	print "Take turns until one player reaches or passes 100 points."
	print "you can roll as many times as you like until you roll a one."
	print "When a one is rolled your turn ends and your turn points go down to zero."
	print

def total_points():
	total1 += turn_points(1)
	total2 += turn_points(2)
	print total1
	print total2

def main():
	total1 = 0
	total2 = 0
	grandtotal1 = 0
	grandtotal2 = 0
	show_instructions()
	while grandtotal1 < 100 and grandtotal2 < 100:
		total1 = take_turn(1)
		total2 = take_turn(2)
		grandtotal1 += total1
		grandtotal2 += total2
		print "player 1 Total:",grandtotal1
		print "Player 2 Total:",grandtotal2
	if grandtotal1 > grandtotal2:
		print "Player One Wins!"
	elif grandtotal2 > grandtotal1:
		print "player Two Wins!"
	else:
		print "Tie Game"
		take_turn(player)
main()



