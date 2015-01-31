import shutil
import os
import time
import datetime
import math
import urllib
import re
from array import array

#only implement this to get info from web
def pullfromnet():
    #filehandle=urllib.urlopen("http://cit.cs.dixie.edu/cs/2420/ssn/InsertNames.txt")
    #filehandle=urllib.urlopen("http://cit.cs.dixie.edu/cs/2420/ssn/RetrieveNames.txt")
    #filehandle=urllib.urlopen("http://cit.cs.dixie.edu/cs/2420/ssn/DeleteNames.txt")
    for line in filehandle.readlines():
        line = line.rstrip()
        if line != '':
            print line
    filehandle.close()

#puts info from web into python list format
def studentlist():
    #fin=open("studentlist.txt","r")
    #fin=open("retrievenames.txt","r")
    #fin=open("deletenames.txt","r")
    count=0
    for line in fin:
        words=line.split()
        print words
        count+=1
        if count<0:
            print words

def removeduplicates(a):
    count=0
    newlist=[]
    fin=a
    t1=time.time()
    for line in fin:
        words=line.split()
        studentssn=student(words[0],words[1],words[2],words[3],words[4])
        toadd=True
        if(count<fin):
            for j in newlist:
                if j==studentssn:
                    toadd=False
        if toadd:
            newlist.append(studentssn)
            count+=1
    
    t2=time.time()
    dt=t2-t1
    print "There are", count, "students"
    print "It took", dt, "seconds"
    
def averageage(a):
    agelist=[]
    agesum=0
    ageave=0
    count=0
    fin=a
    t1=time.time()
    for line in fin:
        count+=1
        words=line.split()
        studentage=student(words[0],words[1],words[2],words[3],words[4])
        s=student.getage(studentage)
        agelist.append(s)
    for i in agelist:
        agesum+=agelist[i]
    ageave=agesum/count
    
    t2=time.time()
    dt=t2-t1
    print "The average age is",ageave,"years."
    print "It took",dt,"seconds"

def deletsudents(a,b):
    beginlist=[]
    delssnlist=[]
    studentssnlist=[]
    
    studentcount=0
    deletedcount=0
    t1=time.time()
    beginlist=a
    deletein=b
    
    for obj in beginlist:
        studentcount+=1
        words=obj.split()
        studentssn=student(words[0],words[1],words[2],words[3],words[4])
        s=student.getssn(studentssn)
        studentssnlist.append(s)

    for delete in deletein:
        w=delete
        delssnlist.append(w)


    beginlistnum=0
    delindex=[]
    for w in delssnlist:
        for j in studentssnlist:
            if w==j:
                x=studentssnlist.index(j)
                delindex.append(x)

    pointer=1
    for q in delindex:
        beginlist[q],beginlist[pointer]=beginlist[pointer],beginlist[q]
        pointer+=1

    beginlist[:pointer]=[]
    
    print pointer,"Students out of",studentcount,"students were deleted"
    t2=time.time()
    dt=t2-t1
    print "It took",dt,"to delete the students."

    

def retrievestudents(a,c):
    agesum=0
    ageave=0
    count=0
    studentin=a
    retrievein=c
    t1=time.time()
    retssnlist=[]
    studentssnlist=[]
    notfound=[]
    agelist=[]
    retrieveagelist=[]
    for ret in retrievein:
        w=ret
        w=w.strip()
        retssnlist.append(w)


    for line in studentin:
        count+=1
        words=line.split()
        studentssn=student(words[0],words[1],words[2],words[3],words[4])
        s=student.getssn(studentssn)
        studentssnlist.append(s)
        age=student.getage(studentssn)
        agelist.append(age)
        
    for i in retssnlist:
        for j in studentssnlist:
            if i==j:
                x=studentssnlist.index(j)
                al=agelist[x]
                retrieveagelist.append(al)
    for num in retssnlist:
        if num not in studentssnlist:
            notfound.append(num)
    for ind in notfound:
        print "student not found:",ind

    for k in retrieveagelist:
        agesum+=k
    ageave=agesum/count
    
    t2=time.time()
    dt=t2-t1
    print "The average age is",ageave,"years."
    print "It took",dt,"seconds"

    
class student:
    def __init__(self,last,first,ssn,email,age):
        self.last=last
        self.first=first
        ssn1=ssn.replace("-","")
        ssn2=ssn1.replace(",","")
        ssn3=ssn2.replace("'","")
        self.ssn=ssn2
        self.email=email
        age1=age.replace("'","")
        age2=age1.replace("]","")
        self.age=int(age2)

    def __eq__(self,rhs):
        if self.ssn==rhs.ssn:
            print "Error: SSN",self.ssn,"is a duplicate."
            return True
        return False

    def getage(self):
        return self.age

    def getssn(self):
        return self.ssn

def main():
    ina=open("studentlist.py","r")
    inb=open("deletenames.py","r")
    inc=open("retrievenames.py","r")
    a=[]
    b=[]
    c=[]
    for students in ina:
        a.append(students)
    for delete in inb:
        w=delete
        w=w.replace(w[0:1],"")
        w=w.replace("-","")
        w=w.replace(w[-2:-1],"")
        w=w.strip()
        b.append(w)
    for ret in inc:
        w=ret
        w=w.replace(w[0:1],"")
        w=w.replace("-","")
        w=w.replace(w[-2:-1],"")
        w=w.strip()
        c.append(w)
    #pullfromnet()
    #studentlist()
    removeduplicates(a)
    averageage(a)
    deletsudents(a,b)
    retrievestudents(a,c)

main()
