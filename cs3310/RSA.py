import os
import sys
import math
import random


sys.setrecursionlimit(10000000)
alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?! \t\n\r"
phrase1="nowforsomequalitytimetoreadsomeofmyoldfavoriteshoneyroastedpeanutsingrediantssaltartificialhoneyroastingagentspressedpeanutsweepingsmmmahthelastpeanutoverflowingwiththesaltandoilsofitsdeardepartedbros"
phrase2="HelloandagainwelcometotheApertureScienceComputerAidedEnrichmentCenterYousubjectnameheremustbetheprideofsubjecthometownherePleasenotethatwehaveaddedaconsequenceforfailureAnycontactwiththechamberfloorwi"
phrase3="AllrightIvebeenthinkingWhenlifegivesyoulemonsdontmakelemonadeMakelifetakethelemonsbackGetmadIdontwantyourdamnlemonsWhatamIsupposedtodowiththeseDemandtoseelifesmanagerMakeliferuethedayitthoughtitcouldgiveCaveJohnsonlemonsDoyouknowwhoIamImthemanwhosgonnaburnyourhousedownWiththelemonsImgonnagetmyengineerstoinventacombustiblelemonthatburnsyourhousedown"
def isprime(n):
    k=20
    t=n-1
    s=0
    while t%2==0:
        t/=2
        s+=1
    for i in range(k):
        a=0
        while a==0:
            a=random.randrange(n)
        if miller_rabin(a,s,t,n):
            return True
        else:
            return False

def miller_rabin(a,s,t,n):
    apow=pow(a,t,n)
    if apow==1:
        return True
    for i in range(s-1):
        if apow==n-1:
            return True
        else:
            apow=(apow*apow)%n
    return apow==n-1

def generatekeys(n):
    n=n%pow(10,200)
    #odd check
    if n%2==1:
        n=n
    elif n%2==0:
        n=n+1
    #prime check
    if isprime(n):
        return n
    else:
        while not isprime(n):
            n=n+2
    return n

def tobase10(string):
    v=0
    for char in string:
        p=alphabet.find(char)
        if p>=0:
            v*=len(alphabet)
            v+=p
    return v

def frombase10(m):
    listb10=[]
    alphlen=len(alphabet)
    m=m
    r=0
    h=1
    let=0
    while h!=0:
        a=int(m)
        b=int(alphlen)
        h=a/b
        r=alphlen*h-m
        r=a-alphlen*h
        m=h
        let=alphabet[r]
        listb10.append(let)

    listb10.reverse()
    return listb10

#inverse of a%b is the returned x
def inveucal(a, b):
    x,y, u,v = 0,1, 1,0
    while a != 0:
        q,r = b//a,b%a; m,n = x-u*q,y-v*q
        b,a, x,y, u,v = a,r, u,v, m,n
    return x

def makee(e,r):
    e=e%pow(10,100)
    if isprime(e):
        e=e
    else:
        while not isprime(e):
            e=e+2
    if r/e==0:
        e=e+1
        makee(e,r)
    else:
        e=e
    return e

def encryption(inmsg, outmsg):
    public=open("public.txt","r")
    regstring=""
    codestring=""
    for i, line in enumerate(public):
        if i==0:
            n=int(line)
        elif i==1:
            e=int(line)
    for j in inmsg:
        regstring+=str(j)
    block=int(math.log(n,70))
    if block%2!=0:
        block-=1
    while len(regstring) > 0:
        codestring=regstring[:block]
        regstring=regstring[block:]
        processencrypt(codestring, inmsg, outmsg,e,n)

def processencrypt(string, inmsg, outmsg,e,n):
    m=tobase10(string)
    m=int(m)
    cnmsg=pow(m,e,n)
    clmsg=frombase10(cnmsg)
    string=""
    for l in clmsg:
        string+=l
    string+='$'
    print>>outmsg, string

def decryption(inmsg, outmsg):
    private=open("private.txt","r")
    for k, line in enumerate(private):
        if k==0:
            n=int(line)
        elif k==1:
            d=int(line)

    block=int(math.log(n,70))
    if block%2!=0:
        block-=1

    string=""
    for l in inmsg:
        string+=l
    while len(string)>0:
        if string.find('$'):
            a=string.partition('$')
            prossesdecrypt(a[0], inmsg, outmsg,d,n)
            string=a[2]
            string=string.strip()
            ######string=string.strip()###removes unwanted newlines but also spaces
            ######the unwanted newlines are on my encrypted files
        else:
            prossesdecrypt(string, inmsg, outmsg,d,n)

##    while len(string)>0:
##        for i in string:
##            if i in '$':
##                a=string.index('$')
##                print a
##                stringfirstpart=string[:a]
##                print stringfirstpart
##                stringsecondpart=string[a+1:]
##                print stringsecondpart
##                prossesdecrypt(stringfirstpart, inmsg, outmsg,d,n)
##                string=stringsecondpart
##            else:
##                continue


def prossesdecrypt(string, inmsg, outmsg,d,n):
    c=tobase10(string)
    c=pow(c,d,n)
    um=frombase10(c)
    string=""
    for l in um:
        string+=l
    print>>outmsg, string

def main():
    notcreated=False
    encoding=True
    decoding=True
    if notcreated==True:
        string1=phrase1
        string2=phrase2
        string3=phrase3
        p=tobase10(string1)
        q=tobase10(string2)
        e=tobase10(string3)
        p=generatekeys(p)
        q=generatekeys(q)

        n=p*q
        r=(p-1)*(q-1)
        e=makee(e,r)
        d=inveucal(e,r)

        pubout=open("public.txt","w")
        print>>pubout, n
        print>>pubout, e
        pubout.close()

        keysout=open("private.txt","w")
        print>>keysout, n
        print>>keysout, d
        keysout.close()

    if encoding==True:
        inmsg=open("secret.txt","r")
        outmsg=open("codedsecret.txt","w")
        encryption(inmsg, outmsg)
        inmsg.close()
        outmsg.close()

    if decoding==True:
        ins=open("codedsecret.txt","r")
        outs=open("uncoded.txt","w")
        decryption(ins, outs)
        ins.close()
        outs.close()

##    if decoding==True:
##        ins=open("EricBeilmannEncrypted.txt","r")
##        outs=open("Teachersuncoded.txt","w")
##        decryption(ins, outs)
##        ins.close()
##        outs.close()

main()

