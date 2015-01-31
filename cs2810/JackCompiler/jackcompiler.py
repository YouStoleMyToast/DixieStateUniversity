# Jack compiler
# created by Eric Beilmann and Robert and Clauson

import os
import sys
#part one syntax analysis
symbols = "()[]{},;=.+-*/&|~<>"
reservedwords = ['class','constructor','method','function','int','boolean','char','void','var','static','field','let','do','if','else','while','return','true','false','null','this']
class JackTokenizer:
    def __init__(self,filestr):
        self.filestr = filestr

    def gettoken(self, filestr):
        whitecount = 0
        linenum = 0
        filestr=self.removecomments(filestr)
        print filestr
        out=self.istoken(filestr)
        print filestr
        out=self.isint(filestr)
        print filestr
        out=self.isconst(filestr)


        # Here's what I got so far. Feel free to proof read. Also I'm thinking we should 
        # just be chaining the if statements the whole way or make these into functions. 
        # What do you think?

    def removecomments(self, filestr):
        for i in filestr:
            while isspace():
                whitecount += 1
            if i in "/n":
                linenum += 1
        filestr = filestr[whitecount:]
        
        for i in filestr:
            if filestr[i] and filestr[i + 1] in "/":
                commentstart = i
            elif filestr[i] in "'\'" and filestr[i + 1] in "n" and i > commentstart:
                commentend = i - 1
        filestr = filestr[:commentstart] + filestr[commentend:]
        
        for i in filestr:
            if filestr[i] in "/" and filestr[i + 1] in "*":
                commentstart = i
            elif filestr[i] in "*" and filestr[i + 1] in "/":
                commentend = i + 1
        filestr = filestr[:commentstart] + filestr[commentend:]
        return filestr
        
    def istoken(self, filestr):
        for i in filestr:
            if filestr[i] in symbols:
                filestr = filestr[i:]
                return tuple('symbol', str(i), linenum)

    def isint(self, filestr):
        number = ''
        for i in filestr:
            if filestr[i].isdigit():
                number = number + filestr[i]
                filestr = filestr[i:]
                if int(number) > 32767:
                    return "Error: Number too large"

            elif not filestr[i].isdigit() and number != '':
                return tuple('integer', int(number), linenum)
                
            elif not filestr[i].isdigit():
                return False

    def isconst(self, filestr):
        for i in filestr:
            if filestr[i] == '"':
                isConst = True
                while isConst:
                    pass
#part two code generation



def main():
    filestr = ""
    fin = open("Main.jack","r")
    fout = open("Main.xml","w")
    line = fin.read().replace('\r\n', '\n').replace('\r', '\n') 
    filestr += line
    jack=JackTokenizer(filestr)
    jack.gettoken(filestr)
    
main()





            
            
