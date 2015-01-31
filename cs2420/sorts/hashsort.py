import random
    
def main():
    a=[]
    b=[]
    for i in range(10):
        q=random.randrange(1,10,1)
        a.append(q)
        b.append(q)

    hashsort(a)
    checkwork(a,b)

def hashsort(a):
    print a
    s=[]
    t=[]
    for i in range(len(a)):
        s.append(0)
    for i in range(len(a)):
        for j in range(len(a)):
            if j==a[i]:
                f=a[i]
                s[f]+=1
    print s
    for i in range(len(s)):
        while s[i]>0:
            t.append(i)
            s[i]-=1
    print t

def checkwork(a,s):#note check doesn't work but it sorts fine
    s.sort()
    if s==a:
        print "it's in order."
    else:
        print "it is not in order."
            

main()
