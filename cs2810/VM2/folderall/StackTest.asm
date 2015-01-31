@17 // push constant 17
D=A
@SP
AM=M+1
A=A-1
M=D
@17 // push constant 17
D=A
@SP
AM=M+1
A=A-1
M=D
@SP // eq
M=M-1
A=M
D=M
@SP
A=M-1
D=M-D
M=0
@892 // push constant 892
D=A
@SP
AM=M+1
A=A-1
M=D
@891 // push constant 891
D=A
@SP
AM=M+1
A=A-1
M=D
@SP // lt
M=M-1
A=M
D=M
@SP
A=M-1
D=M-D
M=0
@32767 // push constant 32767
D=A
@SP
AM=M+1
A=A-1
M=D
@32766 // push constant 32766
D=A
@SP
AM=M+1
A=A-1
M=D
@SP // gt
M=M-1
A=M
D=M
@SP
A=M-1
D=M-D
M=0
@56 // push constant 56
D=A
@SP
AM=M+1
A=A-1
M=D
@31 // push constant 31
D=A
@SP
AM=M+1
A=A-1
M=D
@53 // push constant 53
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
@112 // push constant 112
D=A
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
@SP // neg
A=M-1
M=-M
@SP // and
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M&D
@82 // push constant 82
D=A
@SP
AM=M+1
A=A-1
M=D
@SP // or
A=M-1
D=M
@SP
AM=M-1
M=0
A=A-1
M=M|D
