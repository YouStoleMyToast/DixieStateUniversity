import random

line1="hello"

def substitution():
    alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"
    alphabetlist= list(alphabet)
    random.shuffle(alphabetlist)
    substitutionalphabet = ""
    line2 = ""
    for char in alphabetlist:
        substitutionalphabet += char
    for c in line1:
        if c in alphabet:
            pos1 = alphabet.find(c)
            line2 += substitutionalphabet[pos1]
          
    print alphabetlist
    print substitutionalphabet

    print "line1: ",line1
    print "line2: ",line2


substitution()
