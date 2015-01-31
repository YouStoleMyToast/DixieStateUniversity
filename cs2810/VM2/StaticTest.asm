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

@SP//pop static 8
AM=M-1
D=M
@StaticTest.8

@SP//pop static 3
AM=M-1
D=M
@StaticTest.3

@SP//pop static 1
AM=M-1
D=M
@StaticTest.1

@StaticTest.3
D=M

@StaticTest.1
D=M

@SP // sub
M=M-1
A=M
D=M
@SP
A=M-1
M=D-M

@StaticTest.8
D=M

@SP // add
AM=M-1
D=M
A=A-1
M=M+D
