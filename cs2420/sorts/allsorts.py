import sys
import random
import math

def bubblesort(a,counts):
    swapped=True
    while swapped==True:
        swapped=False
        for i in range(len(a)-1):
            counts[0]+=1
            if a[i]>a[i+1]:
                counts[1]+=1
                a[i],a[i+1]=a[i+1],a[i]
                swapped=True

def shakersort(a,counts):
    swapped=True
    while swapped==True:
        swapped=False
        for i in range(len(a)-1):
            counts[0]+=1
            if a[i]>a[i+1]:
                counts[1]+=1
                a[i],a[i+1]=a[i+1],a[i]
                swapped=True
        for i in range(len(a[-1:])-1):
            counts[0]+=1
            if a[i]>a[i-1]:
                counts[1]+=1
                a[i],a[i-1]=a[i-1],a[i]
                swapped=True
    
def selectionsort(a, counts):
    for i in range(len(a)):
        for j in range (i,len(a)):
            counts[0]+=1
            if a[j]< a[i]:
                counts[1]+=1
                a[i],a[j]=a[j],a[i]

def quicksort(a,counts):
    if a<=1:
        return
    quicksortR(a,0,len(a)-1,counts)

def quicksortR(a,low,high,counts):
    if (high-low) <= 1:
        return
    p=low
    large=low
    
    for i in range(low+1,high+1):
        counts[0]+=1
        if a[i]<a[p]:
            counts[1]+=1
            large+=1
            a[i],a[large]=a[large],a[i]
    a[p],a[large]=a[large],a[p]
    p=large
    quicksortR(a,low,p-1,counts)
    quicksortR(a,p+1,high,counts)

def modquicksortI(a,counts):
    mid=(len(a)-1)/2
    a[0],a[mid]=a[mid],a[0]
    modquicksort(a,counts)
    
def modquicksort(a,counts):
    if a<=1:
        return
    modquicksortR(a,0,len(a)-1,counts)

def modquicksortR(a,low,high,counts):
    if (high-low) <= 1:
        return
    p=low
    large=low
    for i in range(low+1,high+1):
        counts[0]+=1
        if a[i]<a[p]:
            counts[1]+=1
            large+=1
            a[i],a[large]=a[large],a[i]
    a[p],a[large]=a[large],a[p]
    p=large
    modquicksortR(a,low,p-1,counts)
    modquicksortR(a,p+1,high,counts)

def mergsortR(a,counts):
    if len(a)<=1:
        return
    m=len(a)/2
    l=a[:m]
    r=a[m:]
    mergsortR(l,counts)
    mergsortR(r,counts)
    i=0
    j=0
    k=0
    while i<(len(a)):
        #Empty check goes here
        if l[j]<r[k]:
            counts[0]+=1
            a[i]=l[j]
            j+=1
            i+=1
            if j==(len(l)):
                while k<(len(r)):
                    a[i]=r[k]
                    k+=1
                    i+=1
                break
        else:
            counts[0]+=1
            a[i]=r[k]
            k+=1
            i+=1
            if k==(len(r)):
                while j<(len(l)):
                    a[i]=l[j]
                    j+=1
                    i+=1
                break

def hashsort(a,counts):
    s=[]
    t=[]
    size=0
    for i in range(len(a)):
        s.append(0)
        size+=1
    for i in range(len(a)):
        for j in range(len(a)):
            if j==a[i]:
                f=a[i]
                s[f]+=1
    for i in range(len(s)):
        while s[i]>0:
            t.append(i)
            s[i]-=1
    counts[0]=size
    counts[1]=size

def createrandomdata(size):
    a=[]
    for i in range(size):
        q=random.randrange(1,1000,1)
        a.append(q)
    return a

def createmostlysorteddata(size):
    a=[]
    for i in range(size):
        q=random.randrange(1,1000,1)
        a.append(q)   
    a.sort()
    r=random.randrange(1,size)
    a[0],a[r]=a[r],a[0]
    return a

def main():
    sys.setrecursionlimit(10000000)
    fout = open("rc.csv", "w")
    algorithms = [bubblesort, shakersort, selectionsort, quicksort,modquicksortI,mergsortR,hashsort]
    algorithmnames = ["Bubble",", ", "Shaker", ", ", "Selective", ", ", "Quick", ", ", "Modified Quick", ", ", "Merge", ", ", "Hash", "\n"]



    fout.write("Comparing random data compare count")
    fout.write("\n")
    fout.write(", ")
    for mysortname in algorithmnames:
        fout.write(mysortname)
        
    size = 8
    while size <= 4096:
        logsize=math.log(size,2)
        fout.write(str(logsize) + ", ")
        for mysort in algorithms:
            A = createrandomdata(size)
            ACopy = A[:]
            ACopy.sort()
            counts = [0,0]
            mysort(A, counts)
            if counts[0]!=0:
                counts[0]= math.log(counts[0],2)
            if counts[1]!=0:
                counts[1]= math.log(counts[1],2)
            fout.write(str(counts[0]) + ", ")
        fout.write("\n")
        size *= 2



    fout.write("\n")
    fout.write("\n")
    fout.write("\n")
    fout.write("Comparing random data swap count")
    fout.write("\n")
    fout.write(", ")
    for mysortname in algorithmnames:
        fout.write(mysortname)
        
    size = 8
    while size <= 4096:
        logsize=math.log(size,2)
        fout.write(str(logsize) + ", ")
        for mysort in algorithms:
            A = createrandomdata(size)
            ACopy = A[:]
            ACopy.sort()
            counts = [0,0]
            mysort(A, counts)
            if counts[0]!=0:
                counts[0]= math.log(counts[0],2)
            if counts[1]!=0:
                counts[1]= math.log(counts[1],2)
            fout.write(str(counts[1]) + ", ")
        fout.write("\n")
        size *= 2


    fout.write("\n")
    fout.write("\n")
    fout.write("\n")
    fout.write("Comparing mostly sorted data compare count")
    fout.write("\n")
    fout.write(", ")
    for mysortname in algorithmnames:
        fout.write(mysortname)
    
    size = 8
    while size <= 4096:
        logsize=math.log(size,2)
        fout.write(str(logsize) + ", ")
        for mysort in algorithms:
            B = createmostlysorteddata(size)
            BCopy = B[:]
            BCopy.sort()
            counts = [0,0]
            mysort(B, counts)
            if counts[0]!=0:
                counts[0]= math.log(counts[0],2)
            if counts[1]!=0:
                counts[1]= math.log(counts[1],2)
            fout.write(str(counts[0]) + ", ")
        fout.write("\n")
        size *= 2


    fout.write("\n")
    fout.write("\n")
    fout.write("\n")
    fout.write("Comparing mostly sorted data swap count")
    fout.write("\n")
    fout.write(", ")
    for mysortname in algorithmnames:
        fout.write(mysortname)

    size = 8
    while size <= 4096:
        logsize=math.log(size,2)
        fout.write(str(logsize) + ", ")
        for mysort in algorithms:
            B = createmostlysorteddata(size)
            BCopy = B[:]
            BCopy.sort()
            counts = [0,0]
            mysort(B, counts)
            if counts[0]!=0:
                counts[0]= math.log(counts[0],2)
            if counts[1]!=0:
                counts[1]= math.log(counts[1],2)
            fout.write(str(counts[1]) + ", ")
        fout.write("\n")
        size *= 2

    size = math.log(size,2)
    fout.close()
    
main()
