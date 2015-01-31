# Bryan Pitts
# CS 2420
# Assignment 2

import random

def BubbleSort(A, counts):
	swapped = True
	while swapped:
		swapped = False
		for i in range(len(A)-1):
			counts[0]+=1
			if A[i]>A[i+1]:
				counts[1] +=1
				A[i], A[i+1] = A[i+1], A[i]
				swapped = True

def ShakerSort(A, counts):
	swapped = True
	while swapped:
		swapped = False
		for i in range(len(A)-1):
			counts[0]+=1
			if A[i]>A[i+1]:
				counts[1] += 1
				A[i], A[i+1] = A[i+1], A[i]
				swapped = True

def SelectionSort(badList, counts):
	swapped = True
	while swapped:
		swapped = False
		for i in range(len(badList)-1):
			counts[0]+=1
			selection = i
			for j in range(i+1, len(badList)):
				counts[1]+=1
				if badList[j] < badList[selection]:
					selection = j
					swapped = True
			badList[i], badList[selection] = badList[selection], badList[i]
	return badList

# def QuickSort(A, counts):
	# if len(A)<=1:
		# return
	# QuickSortR(A, counts)
	
# def QuickSortR(A, counts):
	# swapped = True
	# while swapped:
		# swapped = False
		

def CreateRandomData(size):
	A = []
	for i in range(size):
		A.append(random.randrange(0,size))
	return A

def main():
	fout = open("rc.csv", "w")
	algorithms = [BubbleSort, ShakerSort, SelectionSort]
	algorithmnames = ["Bubble",", ", "Shaker", ", ", "Selective", ", ", "Quick", ", ", "Modified Quick", ", ", "Merge", ", ", "Hash", "\n"]
	
	fout.write(", ")
	for mysortname in algorithmnames:
		fout.write(mysortname)
	size = 8
	while size <= 1024:
		fout.write(str(size) + ", ")
		for mysort in algorithms:
			A = CreateRandomData(size)
			ACopy = A[:]
			ACopy.sort()
			counts = [0,0]
			mysort(A, counts)
			fout.write(str(counts[0]) + ", ")
		fout.write("\n")
		size *= 2
	fout.close()

main()