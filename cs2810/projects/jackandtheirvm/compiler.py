import os
import sys

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
        self.token=token
        self.i=0
        self.out=outfile
        self.indent=0
        
    def assertend(self):
        pass
    
    def nextToken(self):
        if self.i>=len(self.tokens):
            fail("no token at",token[2])
        token=self.token[self.i]
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
        
        self.symbolstatic=[]
        self.symbolfield=[]
        self.symbolargument=[]
        self.symbollocal=[]

    def getlocals(self,token):
        localscount=-1
        n=0
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            localsend=self.peek(token,n)
            if localsend[1]=='constructor':
                endfound=True
            else:
                n+=1
                if localsend[0]=="Identifier":
                    localscount+=1
                    
        return localscount

    def getparameters(self,token):
        parametercount=0
        parenstart=self.peek(token,2)
        n=3
        endfound=False
        while n<=len(self.tokenlist)-(1+self.i) and endfound==False:
            parenend=self.peek(token,n)
            if parenend[1]==')':
                endfound=True
            else:
                n+=1
                parametercount+=1
        return parametercount

    def findsymbol(self,token):#finds inside parentheses
        parenstart=self.peek(token,2)
        n=3
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
            elif symbolend[1]=='<':
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
            elif symbolend[1]==')':
                endfound=True
            else:
                n+=1
        if len(symbollist)>0:
            return symbollist[0]

    def expresioncode(self):
        print>>self.fout, 'expressioncode1',"push arg 0"
        print>>self.fout, 'expressioncode2',"push constant 0"
        symbol=self.findsymbol()
        if symbol!=None:
            print>>self.fout, 'expressioncode3',symbol
        

    def encode(self):
        for token in self.tokenlist:
            self.i+=1
            if token[0]=="Keyword":
                
                if token[1]=="class":
                    afterclass=self.peek(token,0)
                    if afterclass[0]=="Identifier":
                        self.classname=afterclass[1]
                        classlocalscount=self.getlocals(token)
                        
                        
                if token[1]=="function":
                    functionname=self.peek(token,1)
                    functionname=functionname[1]
                    print>>self.fout,'functioncode',"function",self.classname+"."+functionname,classlocalscount

                if token[1]=="method":
                    methodname=self.peek(token,1)
                    methodname=methodname[1]
                    paramatercount=self.getparameters(token)
                    print>>self.fout,'methodcode1',"method",self.classname+"."+methodname,paramatercount
                    print>>self.fout,'methodcode2',"push arg 0"
                    print>>self.fout,'methodcode3',"pop pointer 0"

                if token[1]=="constructor":
                    local=0 #hardcoded for now
                    argument=1 #hardcoded for now
                    print>>self.fout,'constructorcode1',"function",self.classname+"."+"new "+str(local)
                    print>>self.fout,'constructorcode2',"push constant",classlocalscount
                    print>>self.fout,'constructorcode3',"call memory.alloc",argument
                    print>>self.fout,'constructorcode4',"pop pointer 0"
                                  

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
                    print >> self.fout,'truecode1',"push constant 1"
                    print >> self.fout,'truecode2',"neg"
                
                if token[1]=="false":
                    print >> self.fout,'falsecode',"push constant 0"
                
                if token[1]=="null":
                    print >> self.fout,'nullcode',"push constant 0"
                
                if token[1]=="this":
                    print >> self.fout,'thiscode',"push pointer 0"
                
                if token[1]=="let":
                    print >> self.fout,'letcode1',"push arg 0"
                    print >> self.fout,'letcode2',"push constant 0"
                    print >> self.fout,'letcode3',self.findsymbol(token)
                    print >> self.fout,'letcode4',"pop arg 0"
                
                if token[1]=="do":
                    hardcode='0' #hardcoded for now
                    n=1
                    functionname=self.peek(token,n)
                    while functionname[0]!="Identifier":
                        functionname=self.peek(token,n)
                        n+=1
                    functionname=functionname[1]
                    print>>self.fout,'docode1',"call",self.classname+"."+functionname,hardcode
                    print>>self.fout,'docode2',"pop temp 0"
                
                if token[1]=="if":
                    ifinparen=self.peek(token,2)
                    
                
                if token[1]=="else":
                    pass
                
                if token[1]=="while":
                    print>>self.fout,'whilecode'
                    expresioncode()
                
                if token[1]=="return":#will need to change one
                    afterreturn=self.peek(token,1)
                    afterreturn=afterreturn[1]
                    if afterreturn==";":
                        print>>self.fout,'returncode1',"return"
                    else:
                        print>>self.fout,'returncode2',"push constant 0"
                        print>>self.fout,'returncode3',"return"
                        
                        
                    
                                  
            if token[0]=="StringConstant":
                self.stringconstant(token)

    def nthToken(self,token,n):
        if self.i>=len(self.tokenlist):
            fail("no token at",token[2])
        self.i+=n
        token=self.tokenlist[self.i]
        return token
    
    def peek(self,token,n):
        token=self.nthToken(token,n)
        self.i-=n
        return token 
        
    def stringconstant(self,token):
        strpointer=1
        print>>self.fout,'stringcode1',"push contant",len(token[1])
        print>>self.fout,'stringcode2',"call string.new", strpointer
        for leter in token[1]:
            print>>self.fout,'stringcode3',"push constant", ord(leter)
            print>>self.fout,'stringcode4',"call string.appendChar 2"
        

def main():
    #fin = open(sys.argv[1])
    fin = open("Ball.Jack","r")
    fout = open("MyBall.txt","w")
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
    finasembly=open("MyBall.vm","w")
    code=GenerateCode(tokenlist,finasembly)
    code.encode()

if __name__ == '__main__':
    main()
