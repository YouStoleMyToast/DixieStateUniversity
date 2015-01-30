import random

def perm(L):
    a=sorted(L,reverse=False)
    print a
    rev=sorted(L,reverse=True)
    n=len(a)-1
    j=n-1
    k=n
    while a != rev:
        j=n-1
        k=n
        while a[j]>a[j+1]:
            j=j-1

        while a[j]>a[k]:
            k=k-1
        a[j],a[k]=a[k],a[j]
        r=n
        s=j+1
        while r > s:
            a[r],a[s]=a[s],a[r]
            r -= 1 
            s += 1
            
        print a

def main():
    a=[]
    x=raw_input('What number do you want to see the permutations of?')
    for i in x:
        i=int(i)
        a.append(i)
    perm(a)

main()
