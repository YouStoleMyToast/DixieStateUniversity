import random
    
def main():
    a=[]
    b=[]
    #create random list
    for i in range(1000):
        q=random.randrange(1,1000,1)
        a.append(q)
        b.append(q)

    bubblesort(a)
    checkwork(a,b)

def bubblesort(a):
    swapped=True
    while swapped==True:
        swapped=False
        for i in range(len(a)-1):
            if a[i]>a[i+1]:
                a[i],a[i+1]=a[i+1],a[i]
                swapped=True
    print a

def checkwork(a,s):
    s.sort()
    if s==a:
        print "it's in order."
    else:
        print "it is not in order."
            

main()
