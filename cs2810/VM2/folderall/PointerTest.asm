@3030 // push constant 3030
D=A
@SP
AM=M+1
A=A-1
M=D
@3040 // push constant 3040
D=A
@SP
AM=M+1
A=A-1
M=D
@32 // push constant 32
D=A
@SP
AM=M+1
A=A-1
M=D
@46 // push constant 46
D=A
@SP
AM=M+1
A=A-1
M=D
@3 // push pointer 0
D=A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@4 // push pointer 1
D=A
@1
D=D+A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP // add
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M+D
@THIS // push this 2
D=M
@2
D=D+A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP // sub
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M-D
@THAT // push that 6
D=M
@6
D=D+A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@SP
A=M-1
D=M
@SP // add
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M+D
