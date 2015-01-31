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
    #open files
    #create listobject
    # go through input file and strip and split
            
####### Traverse #######
    aveage=0
    gtotalage=0.0
    l.traverse(addage)
    #average age
     
######## Delete ########
    #delete students
    
####### Retrieve #######
    #go through your list object and get age of selected students then get the average
        
        


main()
        
