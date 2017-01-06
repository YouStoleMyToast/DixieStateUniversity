
indenttypedic = ['space','tab']
linetypedic = ['decreaser''increaser']
linestarters = ['def ','for ','if ','elif ','else ','while ','def\n','for\n','if\n','elif\n','else\n','while\n']

def main():
    #asciidic1()
    #asciidic2()
    fin = open("test.txt","r")
    #fout = open("fixed/file2.py","w")
    #fmt(fin,fout)
    for line in fin:
        for i in range(len(line)):
            char = str(unichr(i))
            num = str(i)
            print char, num
    fin.close()
    #fout.close()
    
def fmt(fin, fout):
    indentlevel = 0
    #indenttype = findindenttype(fin)
    indenttype = 0
    
    indentsize = findindentsize(fin)
    for line in fin:
        linestring = ""
        for char in line:
            linestring = linestring + char
        linestring = dedent(linestring)
        linestring = colon(linestring)
                    
        indenttypestring = indenttypedic[indenttype]
        indentation = indent(indentlevel, indenttypestring, indentsize)
        fout.write(linestring)

def findindenttype(fin):
    spacecount = 0
    tabcount = 0
    for line in fin:
        if line[0] == " ":
            spacecount+=1
        elif line[0] == "  ":
            tabcount+=1
    if tabcount>spacecount:
        return indenttypedic[0]
    elif tabcount<=spacecount:
        return indenttypedic[1]
    
def findindentsize(fin):
    sizes = []
    spacecount = 0
    for line in fin:
        for char in range(len(line)):
            if line[char] == " ":
                spacecount += 1
            else:
                sizes.append(spacecount)
                break
 
    sortedsizes = sorted(sizes)
    zerocount = 0
    for i in range(len(sortedsizes)):
        if sortedsizes[i] == 0:
            zerocount += 1
        else:
            break
    sortedsizes = sortedsizes[zerocount:]
    print "list",sortedsizes
    sortedsizeslen = len(sortedsizes)
    print "len",sortedsizeslen
    for i in sortedsizes:
        if sortedsizes[i]%sortedsizes[0] == 0 and i == sortedsizes[-1]:
            return sortedsizes[0]
        else:
            pass


        
    
                

def colon(linestring):
    for i in range(len(linestarters)):
        if linestarters[i] == linestring:
            linestring=linestring[:-1]
            linestring=linestring+":\n"
        elif linestarters[i] in linestring:
            if linestring[len(linestring)-2] != ":":
                linestring=linestring[:-1]
                linestring=linestring+":\n"
            elif linestring[len(linestring)-2] == ":":
                linestring=linestring[:-1]
                linestring=linestring+"\n"
    return linestring

def indent(indentlevel, indenttypestring, indentsize):
    indentation = ""
    if indenttypestring == "space":
        for i in range(indentlevel):
            for j in range(indentsize):
                indentation = indentation + " "
    if indenttypestring == "tab":
        indentation = " "
    return indentation
    
def dedent(linestring):
    for i in range(len(linestring)):
        if linestring[0] == " " or linestring[0] == "   ":
            linestring = linestring[1:]
        else:
            return linestring

def asciidic1():
    dicname = "asciidic"
    last = 127
    for i in range(last+1):
        char = repr(unichr(i))
        num = str(i)
        if i == 0:
            print dicname+"={"
            print num+":"+"\""+char+"\","
        elif i != last:
            print num+":"+"\""+char+"\","
        else:
            print num+":"+"\""+char+"\""
            print "}"
            
def asciidic2():
    dicname = "asciidic"
    last = 127
    for i in range(last+1):
        char = str(unichr(i))
        num = str(i)
        if i == 0:
            print dicname+"={"
            print num+":"+"\""+char+"\","
        elif i != last:
            print num+":"+"\""+char+"\","
        else:
            print num+":"+"\""+char+"\""
            print "}"
main()

