import random
    
def main():
    a=[]
    b=[]
    #create random list
    for i in range(10):
        q=random.randrange(1,10,1)
        a.append(q)
        b.append(q)

    mergsortR(a)
    checkwork(a,b)

def mergsortR(a):
    if len(a)<=1:
        return
    print a
    m=len(a)/2
    l=a[:m]
    r=a[m:]
    print l
    print r
    mergsortR(l)
    mergsortR(r)
    print "Merging:", l, "and", r
    i=0
    j=0
    k=0
    while i<(len(a)):
        #Empty check goes here
        if l[j]<r[k]:
            print l[j], "is less than", r[k]
            a[i]=l[j]
            j+=1
            i+=1
            print"click"
            if j==(len(l)):
                print "End of left side reached"
                print "Filling in", r[k:]
                while k<(len(r)):
                    a[i]=r[k]
                    k+=1
                    i+=1
                    print"breakone"
                break
        else:
            print l[j], "is not less than", r[k]
            a[i]=r[k]
            k+=1
            i+=1
            if k==(len(r)):
                print "End of right side reached"
                print "Filling in", l[j:]
                print "altpath"
                while j<(len(l)):
                    a[i]=l[j]
                    j+=1
                    i+=1
                    print"breaktwo"
                break
    print "after sort",a
    
def checkwork(a,s):
    s.sort()
    if s==a:
        print "it's in order."
    else:
        print "it is not in order."
            

main()
