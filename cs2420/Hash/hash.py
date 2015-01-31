import math
import time
import random

class hashtable:
    def __init__(self,size):
        tablesize=2*size+1
        while not self.isprime(tablesize):
            tablesize+=2
        self.tablesize=tablesize
        self.table=[None]*tablesize
        self.count=0
        
    def getcount(self):
        return self.count

    def inccount(self):
        self.count+=1
        
    def insert(self,item):
        ssnitem=student.getssn(item)
        if self.exists(item):
            return False
        index=int(ssnitem)%self.tablesize
        self.count+=1
        while self.table[index]:
            index+=1
            if index>=self.tablesize:
                index-=self.tablesize
        self.table[index]=item
        return True

    def isprime(self,n):
        numlist=[]
        if n==2:
            return True
        elif n%2==0:
            return False
        s=int(math.sqrt(n))
        for i in range(3,s+1,2):
            if n/i==0:
                return False
        return True

    def exists(self,item):
        ssnitem=student.getssn(item)
        index=int(ssnitem)%self.tablesize
        oi=index
        while True:
            if self.table[index] is None:
                return False
            if self.table[index] and self.table[index]==item:
                return True
            index+=1
            if index>=self.tablesize:
                index-=self.tablesize
            if index==oi:
                return False

    def traverse(self,callback):
        for item in self.table:
            if item:
                callback(item)

    def delete(self,item):
        ssnitem=student.getssn(item)
        if not self.exists(item):
            return False
        index=int(ssnitem)%self.tablesize
        while True:
            if self.table[index] and self.table[index]==item:
                self.table[index]=False
                self.count-=1
                return True
            index+=1
            if index>=self.tablesize:
                index-=self.tablesize

    def retrieve(self,item):
        ssnitem=student.getssn(item)
        if not self.exists(item):
            return None
        index=int(ssnitem)%self.tablesize
        if self.table[index] is not None:
            return self.table[index]
        if index>=self.tablesize:
            index-=self.tablesize
    
class student:
    def __init__(self,last,root,ssn,email,age):
        self.last=last
        self.root=root
        ssn1=ssn.replace("-","")
        self.ssn=ssn1
        self.email=email
        self.age=float(age)

    def __eq__(self,rhs):
        if self.ssn==rhs.ssn:
            return True
        return False

    def __ne__(self,rhs):
        if self.ssn!=rhs.ssn:
            return True
        return False

    def __le__(self,rhs):
        if self.ssn<=rhs.ssn:
            return True
        return False
    
    def __lt__(self,rhs):
        if self.ssn<rhs.ssn:
            return True
        return False
    
    def __gt__(self,rhs):
        if self.ssn>rhs.ssn:
            return True
        return False
    
    def __ge__(self,rhs):
        if self.ssn>=rhs.ssn:
            return True
        return False

    def getssn(self):
        return int(self.ssn)

    def getage(self):
        return int(self.age)
    
gtotalage=0.0
def addage(student):
    global gtotalage
    gtotalage+=student.getage()

gretage=0.0
def addretage(student):
    global gretage
    gretage+=student.getage()

def main():
    global gtotalage
    global gretage
    ti=time.time()
    short=False
    small=True
    if short==True:
        ina=open("shortstudentlist.txt","r")
        inb=open("shortdeletenames.txt","r")
        inc=open("shortretrievenames.txt","r")
    if small==True:
        ina=open("studentlist.txt","r")
        inb=open("deletenames.txt","r")
        inc=open("retrievenames.txt","r")
    size=0
    for i in ina:
        size+=1
    l=hashtable(size)
    ina.seek(0)
    
    for studenta in ina:
        studenta=studenta.strip()
        words=studenta.split()
        s=student(words[0],words[1],words[2],words[3],words[4])
        ssn=student.getssn(s)
        if not l.insert(s):
            print "Student",studenta,"was not inserted"

####### Traverse #######
    aveage=0
    gtotalage=0.0
    l.traverse(addage)
    print "gtotalage =",gtotalage
    print "traverse count =",l.getcount()
    avg=float(gtotalage)/l.getcount()
    print "average =",avg
    t2=time.time()
    tit2d=t2-ti
    print "traverse time =",tit2d

######## Delete ########
    for studentb in inb:
        s = student("","",studentb.strip(),"","0")
        if not l.delete(s):
            print "couldn't delete student with ssn",studentb.strip(),"it wasn't found"

    print "post delete count =",l.getcount()
    t3=time.time()
    t2t3d=t3-t2
    print "Delete time =",t2t3d

####### Retrieve #######
    gretage=0.0
    retrievecount=0.0
    for studentc in inc:
        s = student("","",studentc.strip(),"","0")
        q=l.retrieve(s)
        if q:
            addretage(q)
            retrievecount+=1

    print "totalage =",gretage
    print "retrieve count =",retrievecount
    aveage=float(gretage)/retrievecount
    print "average =",aveage
    tf=time.time()
    t3tfd=tf-t3
    print "retrieve time =",t2t3d
    tt=tf-ti
    print "total time =",tt

main()
