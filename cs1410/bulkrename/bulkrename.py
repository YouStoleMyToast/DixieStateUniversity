import sys
import os
import random


extension=['jpeg','jpg','png','gif']

def main():
    if len(sys.argv)<2 or len(sys.argv)>3:
        sys.exit(1)
    root = os.path.abspath(sys.argv[1])
    if not os.path.isdir(root):
        print "Not a valid directory"
        sys.exit(1)
    if len(sys.argv)==3:
        prefix=sys.argv[2]
        print "Directory: "+sys.argv[1]
        print "Prefix: "+sys.argv[2]
    else:
        prefix=os.path.basename(root)
        print "Directory: "+sys.argv[1]
        print "(no prefix)"
    allfiles = os.listdir(root)
    
    matching = filterbyextension(root,allfiles,extension)
    inorder=sortbymtime(root,matching)
    newnames=assignnames(prefix,inorder)
    tempname=maketempname(allfiles)
    script=makescript(inorder,newnames,tempname)
    dorenames(root,script)
        
def filterbyextension(root,allfiles,extension):
    filtered = []
    for i in allfiles:
        dot = i.rfind('.')
        post = i[dot+1:-1]
        post.lower()
        if post in extension:
            filtered.append(i)
    return filtered
    print filtered

def sortbymtime(root,matching):
    listTuples = []
    toReturn = []
    for i in matching:
        pic = os.path.join(root,matching[i])
        time = os.path.getmtime(pic)
        t1 = ((time,matching[i].lower(),matching[i]))
        listTuples.append(t1)
    listTuples.sort()
    for e in listTuples:
        toReturn.append(e[2])
    return toReturn
    print toReturn

def assignnames(prefix, inorder):
    digits=len(str(len(inorder)))
    dict={}
    n=1
    for i in inorder:
        var = inorder[i]
        template='%%0%dd' % digits
        s=template % n
        dict[var] = prefix+s+var[var.rfind('.'):].lower()
        n += 1
    return dict
    print dict
        
def maketempname(allfiles):
    randomNumber = random.randint(1,1000000000)
    while True:
        strNumber = str(randomNumber)
        tempname='__temp'+strNumber+'__'
        if tempname in allfiles:
            randomNumber += 1
        else:
            break
    return tempname
    print tempname

def makescript(inorder,newnames,tempname):
    anotherList = []
    for i in inorder:
        if i not in newnames:
            continue
        if newnames[i] == i:
            del newnames[i]
            continue
        if newnames[i] not in newnames:
            target = newnames[i]
            anotherList.append((i,target))
            del newnames[i]
            continue
        chain=[]
        inthechain={}
        link=i
        while True:
            targetname=newnames[link]
            if targetname in inthechain:
                newnames[link]=tempname   
            else:
                continue
            chain.append(link, targetname)
            inthechain[link]=True
            targetname=link
            if link not in newnames:
                break
            chain.reverse()
            for (old, new) in chain:
                anotherlist.append(new,newnames)
                del newnames[old]
    return anotherList
    print anotherList

def dorenames(root,script):
    for i in script:
        print script[0] + " -> " + script[1]
        oldroot = os.path.join(script[0])
        newroot = os.path.join(script[1])
        if os.path.exists(newroot):
            os.exit(1)
        else:
            os.rename(oldroot,newroot)

main()
