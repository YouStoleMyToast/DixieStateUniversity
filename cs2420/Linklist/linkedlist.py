import time

class node:
    def __init__(self,item,next):
        self.item=item
        self.next=next

class linkedlist:
    def __init__(self):
        self.first=None

    def traverse(self,callback):
        current=self.first
        while current is not None:
            callback(current.item)
            current=current.next

    def count(self):
        count=0
        current=self.first
        while current is not None:
            count+=1
            current=current.next
        return count

    def retrieve(self,item):
        current=self.first
        while current is not None:
            if current.item==item:
                return current.item
            else:
                current=current.next
        return None

    def insert(self,item):
        if not self.exists(item):
            n=node(item,self.first)
            self.first=n
            return True
        else:
            return False

    def exists(self,item):
        current=self.first
        while current is not None:
            if current.item==item:
                return True
            else:
                current=current.next
        return False

    def delete(self,item):
        if not self.exists(item):
            return False
        elif self.first.item==item:
            self.first=self.first.next
            return True
        current=self.first
        while current.next.item != item:
            current=current.next
        current.next=current.next.next
        return True

class student:
    def __init__(self,last,first,ssn,email,age):
        self.last=last
        self.first=first
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
    
gtotalage=0.0
def addage(student):
    global gtotalage
    gtotalage+=student.age

gretage=0.0
def addretage(student):
    global gretage
    gretage+=student.age
      
def main():
    global gtotalage
    global gretage
    ti=time.time()
    ina=open("studentlist.txt","r")
    ina2=open("shortstudentlist.txt","r")
    inb=open("deletenames.txt","r")
    inb2=open("shortdeletenames.txt","r")
    inc=open("retrievenames.txt","r")
    inc2=open("shortretrievenames.txt","r")
    l=linkedlist()
    for studenta in ina:
        studenta=studenta.strip()
        words=studenta.split()
        s=student(words[0],words[1],words[2],words[3],words[4])
        if not l.insert(s):
            print "Student",studenta,"was not found"
            
####### Traverse #######
    aveage=0
    gtotalage=0.0
    l.traverse(addage)
    print "gtotalage =",gtotalage
    print "count =",l.count()
    avg=float(gtotalage)/l.count()
    print "average =",avg
    t2=time.time()
    tit2d=t2-ti
    print "traverse time =",tit2d
     
######## Delete ########
    for studentb in inb:
        s = student("","",studentb.strip(),"","0")
        if not l.delete(s):
            print "couldn't delete student with ssn",studentb.strip(),"it wasn't found"

    print "post delete count =",l.count()
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
    print "count =",retrievecount
    aveage=float(gretage)/retrievecount
    print "average =",aveage
    tf=time.time()
    t3tfd=tf-t3
    print "retrieve time =",t2t3d
    tt=tf-ti
    print "total time =",tt
        


main()
        
