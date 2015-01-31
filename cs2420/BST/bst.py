import time

class node:
    def __init__(self,item):
        self.item=item
        self.L=None
        self.R=None

class linkedlist:
    def __init__(self):
        self.root=None

    def traverse(self,callback):
        self.traverseR(self.root, callback)

    def traverseR(self, current, callback):
        callback(current.item)
        if current.L is not None:
            self.traverseR(current.L, callback)
        if current.R is not None:
            self.traverseR(current.R, callback)

    def count(self):
        return self.countR(self.root)
    
    def countR(self, current):
        if current is None:
            return 0
        return 1+self.countR(current.L)+self.countR(current.R)

    def retrieve(self,item):
        if not self.exists(item):
            return None
        return self.retrieveR(self.root, item)

    def retrieveR(self, current, item):
        if item==current.item:
            return current.item
        elif item < current.item:
            return self.retrieveR(current.L,item)
        elif item > current.item:
            return self.retrieveR(current.R,item)

    def insert(self,item):
        if self.exists(item):
            return False
        n=node(item)
        self.root=self.insertR(self.root,n)
        return True
    
    def insertR(self,current,n):
        if current is None:
            current=n
        elif n.item < current.item:
            current.L=self.insertR(current.L, n)
        else:
            current.R=self.insertR(current.R, n)
        return current
                                   
    def exists(self,item):
        return self.existsR(self.root,item)

    def existsR(self,current,item):
        if current is None:
            return False
        if current.item==item:
            return True
        if item < current.item:
            return self.existsR(current.L,item)
        if item > current.item:
            return self.existsR(current.R,item)

    def delete(self,item):
        if not self.exists(item):
            return False
        self.root=self.deleteR(self.root,item)
        return True
        
    def deleteR(self,current,item):
        if current.item==item:
            #no children case
            if not current.L and not current.R:
                current=None
            #one left child case
            elif not current.R:
                current=current.L
            #one right child case
            elif not current.L:
                current=current.R
            #two children case
            else:
                successor=current.R
                while successor.L:
                    successor=successor.L
                current.item=successor.item
                current.R=self.deleteR(current.R,successor.item)
        else:
            if item < current.item:
                current.L=self.deleteR(current.L,item)
            else:
                current.R=self.deleteR(current.R,item)
        return current

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
        
