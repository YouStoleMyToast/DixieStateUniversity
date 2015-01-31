@10 // push constant 10
D=A
@SP
AM=M+1
A=A-1
M=D
@21 // push constant 21
D=A
@SP
AM=M+1
A=A-1
M=D
@22 // push constant 22
D=A
@SP
AM=M+1
A=A-1
M=D
@36 // push constant 36
D=A
@SP
AM=M+1
A=A-1
M=D
@42 // push constant 42
D=A
@SP
AM=M+1
A=A-1
M=D
@45 // push constant 45
D=A
@SP
AM=M+1
A=A-1
M=D
@510 // push constant 510
D=A
@SP
AM=M+1
A=A-1
M=D
@LCL // push local 0
D=M
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@THAT // push that 5
D=M
@5
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
@ARG // push argument 1
D=M
@1
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
@THIS // push this 6
D=M
@6
D=D+A
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@THIS // push this 6
D=M
@6
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
@SP // sub
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M-D
@R11 // push temp 6
D=A
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
