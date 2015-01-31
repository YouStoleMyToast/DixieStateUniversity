#!/Python27/python
# created by Eric Beilmann and Luke Hansen

import os
import sys

COMMANDS={
    'add':  0,
    'sub':  0,
    'neg':  0,
    'eq':   0, 
    'gt':   0,
    'lt':   0,
    'and':  0,
    'or':   0,
    'not':  0,
    'push': 2,
    'pop':  2
}

SEGMENTS={
    'argument':True,
    'local':True,
    'this':True,
    'that':True,
    'constant':True,
    'pointer':True,
    'temp':True,
    'static':True
}

def fail(errormsg, srclinenum, srcline):
    error='ERROR:',errormsg,' on source line:',srclinenum,srcline
    error=error[0],error[1],error[2]
    error="".join(error)
    print >>sys.stderr,error,srclinenum,srcline
    sys.exit(-1)

def issymbol(string):
    symbol='$._:'
    allsymbols = True
    for i in string:
        if i not in symbol and not i.isalnum():
            allsymbols = False
    return allsymbols

def isconstant(string):
    return string >=0 and string <=32767

def parseline(srcline,srclinenum):
    print srcline
    x = srcline.find('//')
    if x >= 0:
    	srcline = srcline[:x]
    srcline = srcline.strip()
    if srcline=="":
        return None
    srcline=srcline.split()
    if srcline[0] in COMMANDS:
        if len(srcline)-1==COMMANDS[srcline[0]]:
            if len(srcline)-1 > 0:
                if isconstant(int(srcline[2])):
                    if 'push' in srcline and srcline[1] in SEGMENTS:
                        return tuple(srcline)
                    elif 'pop' in srcline and srcline[1] in SEGMENTS:
                        if srcline[1] != 'constant':
                            return tuple(srcline)
                    else:
                        fail('Pop cannot contain constant',srclinenum,srcline)
            return tuple(srcline)
        else:
            fail('Invalid amount pieces found',srclinenum,srcline)
    else:
        fail('Invalid command found',srclinenum,srcline)
        

def parsefile(infile):
    outfile=infile[:-2]
    outfile=os.path.join(infile, outfile)+"asm"
    srclinenum = 1
    for srcline in infile:
        parsedline=parseline(srcline,srclinenum)
        if parsedline is not None:
            print >>outfile, parsedline
        srclinenum+=1
    print "Succesfully Parsed:",base,"\n"
    fout.close()



def processfile(outfile):
    pass
    #c=codewriter(outfile)
    #c.setfilename(outfile)

##class codewriter:
##    def __init__(self,outfile):
##        self.outputfile=outfile
##
##    def setfilename(self,outfile):
##        print "Parsing:",self.outfile
##
##    def writearithmatic(command):
##        #writes assembly code for arithmatic lines
##        pass
##        
##
##    def writepushpop(command,segment,index):
##        #writes assembly code for every possible push/pop command
##        if commandT[0]=='pop':
##            print 'pop'
##
##        if command[0]=='push':
##            print 'push'
##
##    def close():
##        sys.exit(-1)
##


def main():
    if len(sys.argv) != 2:
        print "Use: VM.py filename.asm or directoryname."
        sys.exit(-1)
    pathname=os.path.abspath(sys.argv[1])
    infile=os.path.abspath(sys.argv[1])
    isfile=os.path.isfile(infile)
    isdir=os.path.isdir(infile)
    base=os.path.basename(infile)
    dotloc=base.find('.')
    filename = base[:dotloc]
    filetype = base[dotloc+1:]
    outfile=infile[:-2]
    outfile=os.path.join(infile, outfile)+"asm"

    if filetype =='vm' and isfile:

        parsefile(infile)
        processfile(infile)
        
    elif sys.argv[1]==base and isdir:
        for i in os.listdir(infile):
            dotloc=i.find('.')
            filename = i[:dotloc]
            filetype = i[dotloc+1:]
            if filetype =='vm':
                infile=open(infile,"r")
                npathname=os.path.join(infile, i)
                parsefile(npathname)
                processfile(npathname)

                
            elif filetype !='vm':
                print i,"is not an appropriate file type and will be ignored.\n"

        if not os.listdir(pathname):
            print base,"has no files in it."

    else:
        print "That is not A valid file name."
        sys.exit(-1)

    
    #pathname=os.path.abspath(sys.argv[1])
    #print pathname
    #processfile(pathname)

main()





        
        
