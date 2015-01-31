@7 // push constant 7
D=A
@SP
AM=M+1
A=A-1
M=D
@8 // push constant 8
D=A
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
