@111 // push constant 111
D=A
@SP
AM=M+1
A=A-1
M=D
@333 // push constant 333
D=A
@SP
AM=M+1
A=A-1
M=D
@888 // push constant 888
D=A
@SP
AM=M+1
A=A-1
M=D
@Static.3 // push static 3
D=A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@Static.1 // push static 1
D=A
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
@Static.8 // push static 8
D=A
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
