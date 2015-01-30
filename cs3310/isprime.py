import math
import random

def main():
    n=101
    k=20
    t=n-1
    s=0
    while t%2==0:
        t/=2
        s+=1
    for i in range(k):
        b=random.randint(1,n)
        print b
        if math.pow(b,t)%n==1:
            print "composite"
            return True
        else:
            print "probably prime"
main()
