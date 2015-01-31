from collections import deque

class Graph:
    def __init__(self,adjlist):
        self.adjlist=adjlist
        
    def neighbor(self,i):
        return self.adjlist[i]
            
    def isedge(self,i,j):
        if str(j) in self.adjlist[i]:
            return True
        else:
            return False

    def findpathdepth(self,i,j):
        s=deque()
        path=""
        v=[False]*len(self.adjlist)
        s.append(i)
        c=s[-1]
        v[i]=True
        index=0
        while not len(s)<0:
            n=self.neighbor(int(c))
            if str(j) in n:
                s.append(int(j))
                if s[0]!=i:
                    path+=str(i)
                for i in s:
                    path+=str(i)
                return path
            elif v[index]==False:
                c=n[1]
                s.append(int(n[1]))
                v[index]=True
                index+=1
            elif v[index]==True:
                s.pop()
                index+=1   
        return None
    
    def findpathbreadth(self,i,j):
        pq=deque()
        path=""
        pq.append(i)
        c=pq[i]
        if int(c)==int(j):
            return pq
        while int(c)!=int(j):
            if len(pq)>1 and pq[-1]==j:
                path+=str(j)
                return path
            
            c=pq.popleft()
            path=path+str(c)
            if int(c)==int(j):
                return path
            t=self.adjlist[int(c)]
            for t in self.adjlist[int(c)]:
                if t in "0123456789" and t not in path:
                    pq.append(int(t))

def main():
    fin=open('graphinput.txt','r')
    inputlist=[]
    testlist=[]
    tempadjlist=[]
    adjlist=[]
    edgelist=[]
    pathdepthstr=""
    for line in fin:
        line=line.strip()
        inputlist.append(line)
    vertnum=inputlist[0]
    edgenum=inputlist[1]
    for adjacencies in inputlist[2:int(vertnum)+2]:
        adjlist.append(adjacencies)
    edgebegin=int(vertnum)+2
    edgeend=int(vertnum)+2+int(edgenum)
    for edge in inputlist[edgebegin:edgeend]:
        edgelist.append(edge)
    graphobj=Graph(adjlist)
    x=graphobj.neighbor(2)
    q=graphobj.isedge(1,3)
    testbegin=edgeend
    for test in inputlist[testbegin:]:
        testlist.append(test)
    for tests in testlist:
        i=int(tests[0])
        j=int(tests[2])
        pathdepth=graphobj.findpathdepth(i,j)
        print 'pathdepth of test','('+str(i)+','+str(j)+')',pathdepth
        pathbreadth=graphobj.findpathbreadth(i,j)
        print 'pathbreadth of test','('+str(i)+','+str(j)+')',pathbreadth

main()














