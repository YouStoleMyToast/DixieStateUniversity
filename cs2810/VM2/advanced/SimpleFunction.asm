@LCL // push local 0
D=M
A=D
D=M
@SP
AM=M+1
A=A-1
M=D
@LCL // push local 1
D=M
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
@SP // not
A=M-1
M=!M
@ARG // push argument 0
D=M
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
