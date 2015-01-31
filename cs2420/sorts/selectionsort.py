import random
    
def main():
    a=[]
    b=[]
    #create random list
    for i in range(1000):
        q=random.randrange(1,1000,1)
        a.append(q)
        b.append(q)

    selectionsort(a)
    checkwork(a,b)

def selectionsort(a):
    print a
    for i in range(len(a)):                               
        for j in range (i,len(a)):
            if a[j]< a[i]:
                a[i],a[j]=a[j],a[i]
    print a

def checkwork(a,s):
    s.sort()
    if s==a:
        print "it's in order."
    else:
        print "it is not in order."
            


main()
