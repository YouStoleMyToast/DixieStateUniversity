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
    'pop':  2,
    'return':0,
    'function':2
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
                    elif 'function' in srcline:
                        if srcline[2] != 'constant':
                            return tuple(srcline)
                    elif 'return' in srcline:
                        return tuple(srcline)
                    else:
                        fail('Pop cannot contain constant',srclinenum,srcline)
            srcline=srcline,'arithmetic'
            return tuple(srcline)
        else:
            fail('Invalid amount pieces found',srclinenum,srcline)
    else:
        fail('Invalid command found',srclinenum,srcline)
            

def parsefile(infile):
    returnedString = []
    srclinenum = 1
    for srcline in infile:
        parsedline=parseline(srcline,srclinenum)
        if parsedline is not None:
            srclinenum+=1
            returnedString.append(parsedline)
    return returnedString


class codewriter:
    def __init__(self,outfile,command):
        self.outputfile=outfile
        self.filename=os.path.basename(self.outputfile)[:-4]
        self.eqcounter = 0
        self.ltcounter = 0
        self.gtcounter = 0

    def setfilename(self,outfile):
        self.outfile=outfile

    def writearithmetic(self,arithmetic):
        commandlines=[]
        if arithmetic[0] == 'add':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'D=M',
                '@SP',
                'AM=M-1',
                'M=0',
                'A=A-1',
                'M=M+D']
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'sub':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'D=M',
                '@SP',
                'AM=M-1',
                'M=0',
                'A=A-1',
                'M=M-D']
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'neg':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'M=-M']
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'eq':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'M=M-1',
                'A=M',
                'D=M',
                '@SP',
                'A=M-1',
                'D=M-D',
                'M=0',
                '@_EQ_'+str(self.eqcounter),
                'D;JNE',
                '@SP',
                'A=M-1',
                'M=-1',
                '(_EQ_'+str(self.eqcounter)+')']
            for i in commands:
                commandlines.append(i)
            
        elif arithmetic[0] == 'gt':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'M=M-1',
                'A=M',
                'D=M',
                '@SP',
                'A=M-1',
                'D=M-D',
                'M=0',
                '@_LE_'+str(self.ltcounter),
                'D;JLE',
                '@SP',
                'A=M-1',
                'M=-1',
                '(_LE_'+str(self.ltcounter)+')']
            self.gtcounter += 1
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'lt':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'M=M-1',
                'A=M',
                'D=M',
                '@SP',
                'A=M-1',
                'D=M-D',
                'M=0',
                '@_GE_'+str(self.ltcounter),
                'D;JGE',
                '@SP',
                'A=M-1',
                'M=-1',
                '(_GE_'+str(self.ltcounter)+')']
            self.ltcounter += 1
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'and':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'D=M',
                '@SP',
                'AM=M-1',
                'M=0',
                'A=A-1',
                'M=M&D']
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'or':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'D=M',
                '@SP',
                'AM=M-1',
                'M=0',
                'A=A-1',
                'M=M|D']
            for i in commands:
                commandlines.append(i)

        elif arithmetic[0] == 'not':
            commandlines=[]
            commands=[
                '@SP'+' //'+' '+str(arithmetic[0]),
                'A=M-1',
                'M=!M']
            for i in commands:
                commandlines.append(i)
                
        for i in commandlines:
            print i
            print >>self.outfile, i



    def writepushpop(self,command,segment,index):
        commandlines=[]
        if 'pop' in command:
            commandlines=[]	
            if segment in ['static']:#
                commands=[
                    '@'+self.filename+'.'+str(index)+' '+'//'+str(command)+' '+str(segment)+' '+str(index),
                    'D=A',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)

            elif 'pointer' in segment:
                if index==0:
                    commands=[
                        '@'+str(3+index)+' '+'//'+' '+command+' '+segment+' '+str(index),
                        'D=A', # gives it a 3 I hope.
                        '@R13',
                        'M=D',
                        '@SP',
                        'AM=M-1',
                        'D=M',
                        'M=0',
                        '@R13',
                        'A=M',
                        'M=D']
                    for i in commands:
                        commandlines.append(i)
                            
                elif index==1:
                    commands=[
                        '@'+str(3+index)+' '+'//'+' '+command+' '+segment+' '+str(index),
                        'D=A', #gives it a 4 I hope.
                        '@1',
                        'D=D+A',
                        '@R13',
                        'M=D',
                        '@SP',
                        'AM=M-1',
                        'D=M',
                        'M=0',
                        '@R13',
                        'A=M',
                        'M=D']
                    for i in commands:
                        commandlines.append(i)
            elif segment in ['temp']:#
                commands=[
                    '@R'+str(5+index)+' //'+str(command)+' '+str(segment)+' '+str(index),
                    'D=A',
                    '@'+str(index),
                    'D=D+A',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
            elif segment in ['local']:#
                commands=[
                    '@LCL //'+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
            elif segment in ['argument']:#
                commands=[
                    '@ARG //'+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@'+str(index),
                    'D=D+A',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
            elif segment in ['this']:#
                commands=[
                    '@THIS'+''+'//'+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@'+str(index),
                    'D=D+A',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
            elif segment in ['that']:#
                commands=[
                    '@THAT'+''+'//'+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@'+str(index),
                    'D=D+A',
                    '@R13',
                    'M=D',
                    '@SP',
                    'AM=M-1',
                    'D=M',
                    'M=0',
                    '@R13',
                    'A=M',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
                    
        elif 'push' in command:
            commandlines=[]
            if 'constant' in segment:#
                commands=[
                    '@'+str(index)+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=A',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D']
                for i in commands:
                    commandlines.append(i)
            elif segment in ['static']:#
                commands=[
                    '@'+self.filename+'.'+str(index)+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=A',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D']
                for i in commands:
                    commandlines.append(i)

            elif segment in ['pointer']:#
                if index==0:
                    commands=[
                        '@'+str(3+index)+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                        'D=A',
                        'A=D',
                        'D=M',
                        '@SP',
                        'AM=M+1',
                        'A=A-1',
                        'M=D']
                    for i in commands:
                        commandlines.append(i)
                elif index==1:
                    commands=[
                        '@'+str(3+index)+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                        'D=A',
                        '@1',
                        'D=D+A',
                        'A=D',
                        'D=M',
                        '@SP',
                        'AM=M+1',
                        'A=A-1',
                        'M=D']
                    for i in commands:
                        commandlines.append(i)
            elif segment in ['temp']:#
                commands=[
                    '@R'+str(5+index)+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=A',
                    '@6',
                    'D=D+A',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D',
                    '@SP',
                    'A=M-1',
                    'D=M']
                for i in commands:
                    commandlines.append(i)

            elif segment in ['local']:#
                commands=[
                    '@LCL'+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),'D=M',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D']
                for i in commands:
                    commandlines.append(i)

            elif segment in ['argument']:#
                commands=[
                    '@ARG'+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@1',
                    'D=D+A',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D']
                for i in commands:
                    commandlines.append(i)

            elif segment in ['this']:#
                commands=[
                    '@THIS'+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@'+str(index),
                    'D=D+A',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D']
                for i in commands:
                    commandlines.append(i)

            elif segment in ['that']:#
                commands=[
                    '@THAT'+' '+'//'+' '+str(command)+' '+str(segment)+' '+str(index),
                    'D=M',
                    '@'+str(index),
                    'D=D+A',
                    'A=D',
                    'D=M',
                    '@SP',
                    'AM=M+1',
                    'A=A-1',
                    'M=D',
                    '@SP',
                    'A=M-1',
                    'D=M']
                for i in commands:
                    commandlines.append(i)
                    
            for i in commandlines:
                print i
                print >>self.outfile, i
                    
    def writefunction(self,command,segment,index):
        commandlines=[]
        if 'function' in command:	
            commands=[
                '@'+str(index),
                'D=A',
                '('+segment+')',
                '@SP',
                'AM=M+1',
                'A=A-1',
                'M=0',
                '@'+segment,
                'D=D-1;JGT']
            for i in commands:
                commandlines.append(i)
                
        for i in commandlines:
            print i
            print >>self.outfile, i
            
    def returns(command):
        commandlines=[]
        if 'return' in command:	
            commands=[
                '',
                'Return',
                '',
                ]
            for i in commands:
                commandlines.append(i)

        for i in commandlines:
            print i
            print >>self.outfile, i

                
        
    def writepost(self):
        if self.eqcounter > 0:
            pass
        if self.gtcounter > 0:
            pass

        if self.ltcounter > 0:
            pass
    def close(self):
        sys.exit(-1)


def processfile(cw, outfile, commands):
    cw.setfilename(outfile)
    for i in commands:
        if 'arithmetic' in i:
            cw.writearithmetic(i[0])
        if 'push' in i:
            cw.writepushpop(i[0],i[1],int(i[2]))
        if 'pop' in i:
            cw.writepushpop(i[0],i[1],int(i[2]))
        if 'funtion' in i:
            cw.writefunction(i[0],i[1],int(i[2]))
        if 'return' in i:
            cw.returns(i[0])

def main():
    if len(sys.argv) != 2:
        print "Use: VM.py filename.asm or directoryname."
        sys.exit(-1)
    infile=os.path.abspath(sys.argv[1])
    isfile=os.path.isfile(infile)
    isdir=os.path.isdir(infile)
    base=os.path.basename(infile)
    dotloc=base.find('.')
    filename = base[:dotloc]
    filetype = base[dotloc+1:]
    if filetype =='vm' and isfile:
        print "Parsing:",base
        outfile=infile[:-2]
        outfile=os.path.join(infile, outfile)+"asm"
        fin = open(infile, 'r')
        fout = open(outfile, 'w')
        parsedline = parsefile(fin)
        cw=codewriter(outfile, parsedline)
        print 'this',parsedline
        processfile(cw, fout, parsedline)
        cw.writepost()
        fin.close()
        fout.close()
        print "Succesfully Parsed:",base,"\n"
            
    elif sys.argv[1]==base and isdir:
        print "Parsing the contents of:",base,"\n"
        for i in os.listdir(infile):
            dotloc=i.find('.')
            filename = i[:dotloc]
            filetype = i[dotloc+1:]
            if filetype =='vm':
                infile=os.path.abspath(sys.argv[1])
                infile=os.path.join(infile, i)
                outfile=infile[:-2]
                outfile=os.path.join(infile, outfile)+"asm"
                fin = open(infile, 'r')
                fout = open(outfile, 'w')
                print "Parsing:",os.path.basename(infile),"\n"
                parsedline = parsefile(fin)
                outfile=os.path.basename(infile)[:-3] #gives filename from .vm input without .vm for use in processFile
                cw = codewriter(outfile,parsedline)
                print 'this',parsedline
                processfile(cw,fout,parsedline)
                cw.writepost()
                fin.close()
                fout.close()
                print "Succesfully Parsed:",os.path.basename(infile),"\n"

            elif filetype !='vm':
                print i,"is not an appropriate file type and will be ignored.\n"
                            
        print "Succesfully Parsed the contents of:",base,"\n"
        if not os.listdir(base):
            print base,"has no files in it.\n"               
    else:
        print "That is not A valid file name.\n"
        sys.exit(-1)

main()





            
            
