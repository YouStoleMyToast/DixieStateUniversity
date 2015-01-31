import random

def main():
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"
    printdescription()

        
def printdescription():
    print "This program encrypts and decrypts messages, using multiple encryption methods."
    print "Input files must be in the same directory as this program."
    print "Output files will be created in this same directory."
    print

def startmenu():
    print "Do you want to encrypt or decrypt?"
    print "(e)ncrypt"
    print "(d)ecrypt"
    print "(q)uit"
    y=raw_input()
    if y=='e':
        return y
    elif y=='d':
        return y
    elif y=='q':
        return y
        
def methodmenu():
    print "Which method do you want to use?"
    print "(c)aesarian fixed offset"
    print "(s)ubstitution cipher"
    print "(p)suedo-random offset"
    x=raw_input()
    if raw_input=='c':
        return x
    elif raw_input=='s':
        return x
    elif raw_input=='p':
        return x




main()
