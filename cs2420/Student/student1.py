import shutil
import os
import time
import datetime
import math
import urllib
from array import array

#only implement this to get info from web
def pullfromnet():
    filehandle=urllib.urlopen("http://cit.cs.dixie.edu/cs/2420/ssn/InsertNames.txt")
    for line in filehandle.readlines():
        line = line.rstrip()
        if line != '':
            print line
    filehandle.close()

#puts info from web into python list format
def studentlist():
    fin=open("studentlist.txt","r")
    count=0
    for line in fin:
        words=line.split()
        print words
        count+=1
        if count<0:
            print words

class student:
    def __init__(self,last,first,ssn,email,age):
        self.last=last
        self.first=first
        ssn1=ssn.replace("-","")
        ssn2=ssn1.replace(",","")
        ssn3=ssn2.replace("'","")
        self.ssn=int(ssn3)
        self.email=email
        age1=age.replace("'","")
        age2=age1.replace("]","")
        self.age=int(age2)

    def __eq__(self,rhs):
        if self.ssn==rhs.ssn:
            print "error message: ssn",self.ssn,"is a duplicate."
            return True
        return False

def main():
    #pullfromnet()
    #studentlist()
    count=0
    newlist=[]
    fin=open("studentlist.py","r")
    t1=time.time()
    for line in fin:
        words=line.split()
        studentname=student(words[0],words[1],words[2],words[3],words[4])
        toadd=True
        if(count<fin):
            for j in newlist:
                if j==studentname:
                    toadd=False
        if toadd:
            newlist.append(studentname)
            count+=1
    t2=time.time()
    dt=t2-t1
    print "It took", dt, "seconds"

    print "There are", count, "students"

main()
