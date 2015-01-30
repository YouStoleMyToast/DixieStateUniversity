alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"

def tobase10(string):
    v=0
    for char in string:
        p=alphabet.find(char)
        if p>=0:
            v*=len(alphabet)
            v+=p
    return v


def main():
	instr="hello"
	print tobase10(instr)

main()
