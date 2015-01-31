#James Gubler and Eric Beilmann

import sys

DESTINATIONS = {
    '': '000',
    'M': '001',
    'D': '010',
    'MD': '011',
    'A': '100',
    'AM': '101',
    'AD': '110',
    'AMD': '111'
}
COMPUTATIONS = {
    '0': '0101010',
    '1': '0111111',
    '-1': '0111010',
    'D': '0001100',
    'A': '0110000',
    '!D': '0001101',
    '!A': '0110001',
    '-D': '0001111',
    '-A': '0110011',
    'D+1': '0011111',
    'A+1': '0110111',
    'D-1': '0001110',
    'A-1': '0110010',
    'D+A': '0000010',
    'A+D': '0000010',
    'D-A': '0010011',
    'A-D': '0000111',
    'D&A': '0000000',
    'D|A': '0010101',
    'M': '1110000',
    '!M': '1110001',
    'M+1': '1110111',
    'M-1': '1110010',
    'D+M': '1000010',
    'M+D': '1000010',
    'D-M': '1010011',
    'M-D': '1000111',
    'D&M': '1000000',
    'D|M': '1010101'
}

JUMPS = {
    '': '000',
    'JGT': '001',
    'JEQ': '010',
    'JGE': '011',
    'JLT': '100',
    'JNE': '101',
    'JLE': '110',
    'JMP': '111'
}

SYMBOLS = {
    'SP': '0',
    'LCL': '1',
    'ARG': '2',
    'THIS': '3',
    'THAT': '4',
    'R0': '0',
    'R1': '1',
    'R2': '2',
    'R3': '3',
    'R4': '4',
    'R5': '5',
    'R6': '6',
    'R7': '7',
    'R8': '8',
    'R9': '9',
    'R10': '10',
    'R11': '11',
    'R12': '12',
    'R13': '13',
    'R14': '14',
    'R15': '15',
    'SCREEN': '16384',
    'KBD': '24576',
    
}

def fail(errorMsg, srcLineNum, srcLine):
    print errorMsg, ' On Source Line', srcLineNum, srcLine
    sys.exit(-1)

def isSymbol(string):
    symbol='$._:'
    allsymbols = True
    for i in string:
        if i not in symbol and not i.isalnum():
            allsymbols = False
    return allsymbols

def isConstant(string):
    if string.isdigit():
        if len(string) > 0 and len(string) <=5:
            if int(string) >=0 and int(string) <=32767:
                return True
    return False

def parseLine(srcline, srclinenumber):
    x = srcline.find('//')
    if x >= 0:
    	noComment = srcline[:x]
    else:
	noComment = srcline
    print noComment
    noCom = noComment.strip()
   
    if noCom == "":
        return None
    print noCom
    if '@' in noCom:
        y = noCom.find('@')
        
        
        symbol = noCom[y+1:]
        
        
        if isConstant(symbol) or isSymbol(symbol):
            return('A_INSTRUCTION', symbol, srcline, srclinenumber)
        else:
            
            fail("Not Valid A_INSTRUCTION",srclinenumber, srcline)
            
            
    elif '(' in noCom:
        frontpar = noCom.find('(')
        backpar = noCom.find(')')
        symbol = noCom[frontpar+1:backpar]
        if isSymbol(symbol):
            return('L_INSTRUCTION', symbol, srcline, srclinenumber)
        else:
            fail("Not Valid L_INSTRUCTION",srclinenumber, srcline)
            
    else:
        if '=' in noCom:
            e = noCom.find('=')
            dest = noCom[:e]
            stdest = dest.strip()
            
            if stdest not in DESTINATIONS:
                
                fail("Not Valid DESTINATION",srclinenumber, srcline)
                
            if ';' in noCom:
                c = noCom.find(';')
                jump = noCom[c+1:]
                
                if jump not in JUMPS:
                    fail("Not Valid JUMP",srclinenumber, srcline)
                comp = noCom[e+1:c]
                
                if comp not in COMPUTATIONS:
                    fail("Not Valid COMPUTATION",srclinenumber, srcline)
                return('C_INSTRUCTION', dest, comp, jump, srcline, srclinenumber)
            else:
                jump = ''
                comp = noCom[e+1:]
                
                if comp not in COMPUTATIONS:
                    fail("Not Valid COMPUTATION",srclinenumber, srcline)
                return('C_INSTRUCTION', dest, comp, jump, srcline, srclinenumber)
        else:
            dest = ''
            if ';' in noCom:
                c = noCom.find(';')
                jump = noCom[c+1:]
                
                if jump not in JUMPS:
                    fail("Not Valid JUMP",srclinenumber, srcline)
                comp = noCom[:c]
                
                if comp not in COMPUTATIONS:
                    fail("Not Valid COMPUTATION",srclinenumber, srcline)
                return('C_INSTRUCTION', dest, comp, jump, srcline, srclinenumber)
            else:
                jump = ''
                comp = noCom
                
                if comp not in COMPUTATIONS:
                    fail("Not Valid COMPUTATION",srclinenumber, srcline)
                return('C_INSTRUCTION', dest, comp, jump, srcline, srclinenumber)

def main():
    if len(sys.argv) != 2:
        print "Use: Assembler.py file.asm" 
    result = []
    filename = sys.argv[1]
    period = filename.find('.')
    fname = filename[:period]
    ftype = filename[period:]
    ofile = fname + '.hack'
    
    if ftype != '.asm':
        fail('Wrong File Type, must be .asm', filename, 0)
        
    fin = open(sys.argv[1], 'r')
    fout = open(ofile, 'w')
    
    linenum = 1
    for line in fin:
        
        parsedline = parseLine(line, linenum)
        
        if parsedline is not None:
            
            
            result.append(parsedline)
        linenum+=1
    binaryResult = []
    lin = 0
    for element in result:
        
        if element == 'L_INSTRUCTION':
            if element[1] not in SYMBOLS:
                SYMBOLS[element[1]] = str(lin)
        else:
            lin +=1
    lin = 16
    for elty in result:
        if elty[0] == 'A_INSTRUCTION':
            sym = elty[1]
            if sym not in SYMBOLS:
                if sym.isdigit():
                    SYMBOLS[sym]=sym
                else:
                    SYMBOLS[sym] = str(lin)
            Ainst = SYMBOLS[sym]
            binAinst = int(Ainst)
            binaryResult.append(bin(binAinst)[2:].zfill(16))
        if elty[0] == 'C_INSTRUCTION':
            kind, dst, compy, jmp, q, p = elty
            binCinst = '111' + COMPUTATIONS[compy] + DESTINATIONS[dst] + JUMPS[jmp]
            binaryResult.append(binCinst)
        lin +=1
    for elt in binaryResult:
        fout.write(elt)
        
    fin.close()
    fout.close()

main()

        
          
    
