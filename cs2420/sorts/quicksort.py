import random
    
def main():
    a=[]
    b=[]
    for i in range(10):
        q=random.randrange(1,10,1)
        a.append(q)
        b.append(q)

    print a
    for i in range(len(a)):
        quicksort(a)
    print a
    checkwork(a,b)

def quicksort(a):
    if a<=1:
        return
    quicksortR(a,0,len(a)-1)

def quicksortR(a,low,high):
    if (high-low) <= 1:
        return
    p=low
    large=low
    
    for i in range(low+1,high+1):
        if a[i]<a[p]:
            large+=1
            a[i],a[large]=a[large],a[i]
    a[p],a[large]=a[large],a[p]
    p=large
    quicksortR(a,low,p-1)
    quicksortR(a,p+1,high)
                          
def checkwork(a,s):
    s.sort()
    if s==a:
        order=True
        print "it's in order."
    else:
        order=False
        print "it is not in order."
            

main()
