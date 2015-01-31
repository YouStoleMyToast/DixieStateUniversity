import random
    
def main():
    a=[]
    b=[]
    for i in range(10):
        q=random.randrange(1,10,1)
        a.append(q)
        b.append(q)
    modlist(a)
    for i in range(len(a)):
        modquicksort(a)
    checkwork(a,b)
    
def modlist(a):
    mid=(len(a)-1)/2
    a[0],a[mid]=a[mid],a[0]
    
def modquicksort(a):
    if a<=1:
        return
    modquicksortR(a,0,len(a)-1)

def modquicksortR(a,low,high):
    if (high-low) <= 1:
        return

    p=low
    large=low
    print a
    
    for i in range(low+1,high+1):
        if a[i]<a[p]:
            large+=1
            a[i],a[large]=a[large],a[i]
    a[p],a[large]=a[large],a[p]
    p=large
    modquicksortR(a,low,p-1)
    modquicksortR(a,p+1,high)
                          
def checkwork(a,s):
    s.sort()
    if s==a:
        order=True
        print "it's in order."
    else:
        order=False
        print "it is not in order."
            

main()
