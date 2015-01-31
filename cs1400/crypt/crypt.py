import random

def main():
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"
    printdescription()

    while True:
        encryptordecrypt=startmenu()
        if encryptordecrypt=='q':
            break
        method=methodmenu()
        sourcefile=raw_input("enter the file name to be encrypted or decrypted:")
        destinationfile=raw_input("enter the name of the new file you will be creating:")
        password=raw_input("enter the password:")
        fin = open(sourcefile, "rb")
        fout = open(destinationfile, "wb")
        random.seed(password)
        if method=='c':
            Caesarian(fin,fout,encryptordecrypt,alphabet)
        elif method=='s':
            substitution(fin,fout,encryptordecrypt,alphabet)
        elif method=='p':
            psuedorandom(fin,fout,encryptordecrypt,alphabet)
        fin.close()
        fout.close()
        
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
    return y
        
def methodmenu():
    print "Which method do you want to use?"
    print "(c)aesarian fixed offset"
    print "(s)ubstitution cipher"
    print "(p)suedo-random offset"
    x=raw_input()
    return x

def Caesarian(fin, fout, encrypt_or_decrypt_choice, alphabet):
    # Determine the offset by generating a random number in the correct range.
    # This will be the same random number, if the password sent to random.seed is the same.
    offset = random.randrange(1,len(alphabet))
    if encrypt_or_decrypt_choice=='d':
        offset = -offset
    print "Using the secret offset of", offset

    # Read every line of the input file.
    for line1 in fin:
        # Alter each character of the line1, putting the result into line2.
        line2 = ""
        for c in line1:
            if c in alphabet:
                pos1 = alphabet.find(c)
                pos2 = (pos1+offset)%len(alphabet)
                line2 += alphabet[pos2]
        # Write each resulting line2 to the output file.
        fout.write(line2)

def substitution(fin, fout, encrypt_or_decrypt_choice, alphabet):
    offset = random.randrange(1,len(alphabet))
    if encrypt_or_decrypt_choice=='d':
        offset = -offset

    for line1 in fin:
        line2 = ""
        for c in line1:
            if c in alphabet:
                alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"
                alphabetlist= list(alphabet)
                random.shuffle(alphabetlist)
                pos1 = alphabet.find(c)
                pos2 = (pos1+offset)%len(alphabet)
                line2 += alphabet[pos2]
        fout.write(line2)
        
def psuedorandom(fin,fout,encrypt_or_decrypt_choice,alphabet):
    for line1 in fin:
        line2 = ""
        for c in line1:
            if c in alphabet:
                offset = random.randrange(1,len(alphabet))
                if encrypt_or_decrypt_choice=='d':
                    offset = -offset
                pos1 = alphabet.find(c)
                pos2 = (pos1+offset)%len(alphabet)
                line2 += alphabet[pos2]
        fout.write(line2)
    
main()
