import os
import sys
import string

SYMBOLS = "()[]{},;=.+-*/&|~<>"
INTEGER = "0123456789"
LINE_COUNT = 0
KEYWORD = ['class',
           'constructor',
           'function',
           'method',
           'field',
           'static',
           'var',
           'int',
           'char',
           'boolean',
           'void',
           'true',
           'false',
           'null',
           'this',
           'let',
           'do',
           'if',
           'else',
           'while',
           'return']
class JackTokenizer:
    def __init__(self, filelist):
        self.f = filelist
        if not self.f.endswith('\n'):
                self.f = self.f + '\n'
                
    def getToken(self):
        global LINE_COUNT
        fleng=len(self.f)
        outlist = []
        wholenumber = ''
        ifn=self.f.find('\n')
        while fleng > 0:
            fleng=len(self.f)
            ifn=self.f.find('\n')
            counter=0
            if fleng==0:
                return outlist
            if self.f.startswith('\n'):
                self.f=self.f.strip()
                LINE_COUNT += 1
            if self.f[counter] == '\n' :
                LINE_COUNT += 1
            if counter > 0:
                self.f = self.f[counter:]
                counter=0
                continue
            if self.f.startswith('//'):
                counter=0
                while(counter < len(self.f)) and self.f[counter] != '\n':
                        counter += 1
                LINE_COUNT += 1
            if counter > 0:
                self.f = self.f[counter + 1:]
                continue
            if (self.f.startswith('/*')):
                counter = 2
                commentLoc = self.f.find('*/')
                if self.f[counter] != '/':
                    while (counter < len(self.f)):
                        if (self.f[counter] is '*' and self.f[counter +1] is '/'):
                            LINE_COUNT += 1
                            break
                        else:
                            if self.f[counter] == '\n':
                                LINE_COUNT += 1
                            counter += 1
            if self.f.startswith(' '):
                self.f=self.f[1:]
            if counter > 0:
                self.f = self.f[commentLoc + 2:]
                continue
            if self.f[0] in SYMBOLS:
                outlist.append(('Symbol', self.f[0], LINE_COUNT))
                self.f = self.f[1:]
                continue
            if self.f[0] in INTEGER:
                counter = 1
                while self.f[counter] in INTEGER:
                    counter += 1
                wholenumber = self.f[:counter]
                if not wholenumber > 32768:
                    break
                outlist.append(('Integer', wholenumber, LINE_COUNT))
            if counter > 0:
                self.f = self.f[counter:]
                continue
            if self.f[0] is '"':
                comStart = self.f.find('"')
                self.f = self.f[comStart+1:]
                foundNL = self.f.find('\n')
                commentend = self.f.find('"')
                if foundNL > commentend:
                    stringConstant = self.f[:commentend + 1]
                    stringConstant = '"' + stringConstant
                    self.f = self.f[commentend + 1:]
                    outlist.append(('StringConstant', stringConstant, LINE_COUNT))
                else:
                    print 'Found new line char before comment end', LINE_COUNT
            if self.f[0] is '\n':
                LINE_COUNT += 1
                self.f = self.f[:]
            if self.f[0].isalnum() or self.f[0] == '_':
                counter = 1
                while self.f[counter].isalnum() or self.f[counter] == '_':
                    counter += 1
                key = self.f[:counter]
                if key in KEYWORD:
                    outlist.append(('Keyword', key, LINE_COUNT))
                else:
                    outlist.append(('Identifier', key, LINE_COUNT))
                self.f = self.f[counter:]
                continue
            fleng=len(self.f)
            if fleng==0:
                return outlist
            
#part two code generation
class CompilationEngine:
    def __init__(self,token,outfile):
        token=token
        self.i=0
        self.out=outfile
        self.indent=0
        
    def assertend(self):
        pass
    
    def nextToken(self):
        if self.i>=len(tokens):
            fail("no token at",token[2])
        token=token[self.i]
        self.i+=1
        global glinenum
        glinenum=token[2]
        return token

    def peek(self):
        token=self.nextToken()
        self.i-=1
        return token

    def keyword(self):
        token=self.nextToken()
        if token[0]!=KEYWORD or token[1]!=KEYWORD:
            fail("your fail message here")
        print>>self.out," "*self.indent, "<keyword>", token[1] ,"</keyword>"
        return token

    def identifier(self):
        token=self.nextToken()
        if token[0]!=keyword or token[1]!=keyword:
            fail("your fail message here")
        print>>self.out," "*self.indent, "<identifier>", token[1], "</identifier>" 
        return token

    def symbol(self):
        token=self.nextToken()
        if token[0]!=SYMBOLS or token[1]!=SYMBOLS:
            fail("your fail message here")
        print>>self.out," "*self.indent, "<symbol>", token[1], "</symbol>"
        return token

    def expectType(self):
        token=self.peek()
        if token[0]==keyword and token[1] in ['int', 'char', 'boolean']:
            return self.keyword(token[1])
        return self.identifier
        
    def compileClass(self):
        #about 5 lines I missed
        kind=self.keyword(token[1])
        vartype=self.expectType()
        while True:
            token=self.peek()
            if token[0]!=keyword or token[1] not in ['static','field']:
                break
            #self.compile classVarDec()
        while True:
            token=self.peek()
            if token[0]!=symbol or token[1]!=',':
                break
            self.compileSubroutine()
            
###########################################################################
            
class GenerateCode:
    def __init__(self,tokenlist,finassembly):
        self.tokenlist=tokenlist
        self.fout=finassembly
        self.i=0
        self.classname=None
        self.popcount=0
        
        self.symbolstatic=[]
        self.symbolfield=[]
        self.symbolargument=[]
        self.symbollocal=[]

    def getlocals(self,token):
        localslist=[]
        n=0
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            localsend=self.peek(token,n)
            if localsend[1]=='constructor':
                endfound=True
            else:
                n+=1
                if localsend[0]=="Identifier":
                    localslist.append(localsend[1])
        return localslist

    def getfields(self,token):
        fieldslist=[]
        n=0
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            localsend=self.peek(token,n)
            if localsend[1]=='constructor':
                endfound=True
            elif localsend[1]=="field":
                while localsend[1]!=';' and n<=len(self.tokenlist)-(2+self.i):
                    localsend=self.peek(token,n)
                    n+=1
                    if localsend[0]=="Identifier":
                        field=localsend[1]
                        fieldslist.append(field)
            else:
                n+=1
        return fieldslist

    def getparameters(self,token):
        paralist=[]
        parenstart=self.peek(token,2)
        n=3
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            parenend=self.peek(token,n)
            if parenend[1]==')':
                endfound=True
            elif parenend[0]=="Identifier":
                n+=1
                paralist.append(parenend[1])
            return paralist
        

    def findsymbol(self,token):#finds inside parentheses
        parenstart=self.peek(token,2)
        n=1
        symbollist=[]
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            symbolend=self.peek(token,n)
            if symbolend[1]=='+':
                symbollist.append("add")
                n+=1
            elif symbolend[1]=='-':
                symbollist.append("sub")
                n+=1
            elif symbolend[1]=='*':
                symbollist.append("call math.multiply 2")
                n+=1
            elif symbolend[1]=='/':
                symbollist.append("call math.divide 2")
                n+=1
            elif symbolend[1]=='&':
                symbollist.append("and")
                n+=1
            elif symbolend[1]=='|':
                symbollist.append("or")
                n+=1
            elif symbolend[1]=='>':
                symbollist.append("gt")
                n+=1
            elif symbolend[1]=='<':
                symbollist.append("lt")
                n+=1
            elif symbolend[1]=='=':
                symbollist.append("eq")
                n+=1
            elif symbolend[1]=='-':
                symbollist.append("neg")
                n+=1
            elif symbolend[1]=='~':
                symbollist.append("not")
                n+=1
            elif symbolend[1]==')' or symbolend[1]==';':
                endfound=True
            else:
                n+=1
        for sym in symbollist:
            if sym!="eq":
                return symbollist
            else:
                return
            
    def foundbyendofline(self,token):
        n=1
        endseek=self.peek(token,n)
        while endseek[1]!=";":
            n+=1
            if endseek[1]==token:
                return True
            else:
                return False
        
    def encode(self):
        elseflag=False
        returnflag=False
        elsecount=0
        whilecount=0
        ifcount=0
        for token in self.tokenlist:
            (x,y,z)=token
            newx=""
            newy=""
            for i in x:
                i=str(i)
                if str(i) in string.printable:
                    newx=newx+i
                    newx=newx.strip()
            for j in y:
                j=str(j)
                if str(j) in string.printable:
                    newy=newy+j
                    newy=newy.strip()
            x=newx
            y=newy
            token=(x,y,z)
            self.i+=1
            #last part of else
            if token[1]=="}" and elseflag==True:
                print>>self.fout,"lable IF_END_"+str(elsecount)
                
            beforereturn=self.peek(token,-1)
            (x,y,z)=beforereturn
            if returnflag==True and y=="THIS":
                pass
            
            if token[0]=="Keyword":
                
                if token[1]=="class":
                    afterclass=self.peek(token,0)
                    if afterclass[0]=="Identifier":
                        self.classname=afterclass[1]
                        classlocals=self.getlocals(token)
                        fieldscount=len(self.getfields(token))
                        
                if token[1]=="function":
                    para=self.getparameters(token)
                    args=len(para)
                    functionname=self.peek(token,1)
                    functionname=functionname[1]
                    print>>self.fout,"function",self.classname+"."+functionname,fieldscount

                if token[1]=="method":
                    para=self.getparameters(token)
                    args=len(para)
                    methodparameters=self.getparameters(token)
                    methodname=self.peek(token,1)
                    methodname=methodname[1]
                    print>>self.fout,"function",self.classname+"."+methodname,args
                    print>>self.fout,"push argument 0"
                    print>>self.fout,"pop pointer 0"

                if token[1]=="constructor":
                    para=self.getparameters(token)
                    args=len(para)+1
                    local=0 #hardcoded for now
                    print>>self.fout,"function",self.classname+"."+"new "+str(local)
                    print>>self.fout,"push constant",fieldscount
                    print>>self.fout,"call Memory.alloc",args
                    print>>self.fout,"pop pointer 0"
                                  

                if token[1]=="fieled":
                    pass

                if token[1]=="static":
                    pass

                if token[1]=="var":
                    pass

                if token[1]=="int":
                    pass

                if token[1]=="char":
                    pass

                if token[1]=="boolean":
                    pass
                
                if token[1]=="void":
                    pass
                
                if token[1]=="true":
                    print >> self.fout,"push constant 1"
                    print >> self.fout,"neg"
                
                if token[1]=="false":
                    print >> self.fout,"push constant 0"
                
                if token[1]=="null":
                    print >> self.fout,"push constant 0"
                
                if token[1]=="this":
                    print >> self.fout,"push pointer 0"
                
                if token[1]=="let":
                    #letcode
                    n=0
                    line=self.peek(token,n)
                    (x,y,z)=line
                    while ";"is not y:
                        line=self.peek(token,n)
                        (x,y,z)=line
                        line=line[0]
                        line=line.strip()
                        o=n+1
                        p=o+1
                        q=p+1
                        r=q+1
                        intcheck1=self.peek(token,n)
                        intcheck2=self.peek(token,o)
                        intcheck3=self.peek(token,p)
                        intcheck4=self.peek(token,q)
                        lineend=self.peek(token,r)
                        n+=1
                        line=(x,y,z)
                    prelineend=self.peek(line,0)
                    (x,y,z)=prelineend
                    if x=="Integer":
                        print >> self.fout,"push constant",y
                        #print >> self.fout,"pop this",self.popcount
                        self.popcount+=1
                        n+=1
                    elif x!="Integer":
                        print >> self.fout,"push argument",self.popcount
                        print >> self.fout,"pop this",self.popcount

                        self.popcount+=1
                        n+=1
                    else:
                        n+=1

                
                if token[1]=="do":
                    #docode
                    hardcode='0' #hardcoded for now
                    n=2
                    classname=self.peek(token,n)
                    (x,y,z)=classname
                    if x=="symbol":
                        classname=y
                    else:
                        classname=self.classname
                    
                    n=0
                    functionname=self.peek(token,n)
                    functionname=functionname[1]
                    print>>self.fout,"call",str(classname)+"."+str(functionname),hardcode
                    print>>self.fout,"pop temp 0"

                if token[1]=="if":
                    #expressioncode
                    print>>self.fout, "push argument 0"
                    print>>self.fout, "push constant 1"
                    symbol=self.findsymbol(token)
                    if symbol!=None:
                        print>>self.fout, symbol[0]
                    #expresioncode end
                    print>>self.fout,"not"
                    print>>self.fout,"if.goto IF_ELSE_"+str(ifcount)

            
                if token[1]=="else":
                    print>>self.fout,"goto IF_EXIT_"+str(elsecount)
                    print>>self.fout,"label IF_ELSE_"+str(elsecount)
            
                if token[1]=="while":
                    print "while>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
                    print>>self.fout,"Label WHILE_EXIT_"+str(whilecount)
                    nexttoken=self.peek(token,0)
                    print nexttoken
                    #expressioncode
                    print>>self.fout, "push argument 0"
                    print>>self.fout, "push constant 1"
                    symbol=self.findsymbol(token)
                    if symbol!=None:
                        print>>self.fout, symbol[0]
                    #expresioncode end
                    
                    print>>self.fout,"not"
                    
                    print>>self.fout,"if.goto WHILE_EXIT_"+str(whilecount)
                    
                    #statementcode
                    #docode
                    hardcode='0' #hardcoded for now
                    n=2
                    classname=self.peek(token,n)
                    (x,y,z)=classname
                    if x=="symbol":
                        classname=y
                    else:
                        classname=self.classname
                        
                    #letcode
                    n=0
                    line=self.peek(token,n)
                    (x,y,z)=line
                    while ";"is not y:
                        line=self.peek(token,n)
                        (x,y,z)=line
                        line=line[0]
                        line=line.strip()
                        o=n+1
                        p=o+1
                        q=p+1
                        r=q+1
                        intcheck1=self.peek(token,n)
                        intcheck2=self.peek(token,o)
                        intcheck3=self.peek(token,p)
                        intcheck4=self.peek(token,q)
                        lineend=self.peek(token,r)
                        n+=1
                        line=(x,y,z)
                    prelineend=self.peek(line,0)
                    (x,y,z)=prelineend
                    if x=="Integer":
                        print >> self.fout,"push constant",y
                        #print >> self.fout,"pop this",self.popcount
                        self.popcount+=1
                        n+=1
                    elif x!="Integer":
                        print >> self.fout,"push argument",self.popcount
                        print >> self.fout,"pop this",self.popcount

                        self.popcount+=1
                        n+=1
                    else:
                        n+=1
                    #statementcode end
                    print>>self.fout,"goto WHILE_TEST_"+str(whilecount)
                    print>>self.fout,"local WHILE_EXIT_"+str(whilecount)

                
                if token[1]=="return":#will need to change one
                    returnflag=True
                    afterreturn=self.peek(token,0)
                    afterreturn=afterreturn[1]
                    if afterreturn==";":
                        print>>self.fout,"return"
                    else:
                        print>>self.fout,"push constant 0"
                        print>>self.fout,"return"
                        
            if token[0]=="StringConstant":
                self.stringconstant(token)
            
    def nthToken(self,token,n):
        if self.i>=len(self.tokenlist):
            pass
        self.i+=n
        token=self.tokenlist[self.i]
        return token
    
    def peek(self,token,n):
        token=self.nthToken(token,n)
        self.i-=n
        return token 
        
    def stringconstant(self,token):
        strpointer=1
        print>>self.fout,"push contant",len(token[1])
        print>>self.fout,"call string.new", strpointer
        for leter in token[1]:
            print>>self.fout,"push constant", ord(leter)
            print>>self.fout,"call string.appendChar 2"
        

def main():
    fin = open(sys.argv[1])
    fout = open("Tokenslist.txt","w")
    tokenlist=[]
    filelist = ''
    filelisttemp = fin.read().replace('\r\n', '\n').replace('\r', '\n').replace('\t', '')
    for line in filelisttemp:
        filelist = filelist + line
    jack = JackTokenizer(filelist)
    token = jack.getToken()
    for triple in token:
        tokenlist.append(triple)
        print >>fout, triple
    fin.close()
    fout.close()
    #Parser
    #finxml=open("tokenlist.txt","r")
    #foutxml=open("tokenlist.xml","w")
    #parsed=CompilationEngine(tokenlist,foutxml)
    #foutxml.close()
    #generating assembly
    finasembly=open("Thevmcode.vm","w")
    code=GenerateCode(tokenlist,finasembly)
    code.encode()

if __name__ == '__main__':
    main()
