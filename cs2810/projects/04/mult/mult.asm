	@R2
	M=0
	@R1
	D=M
	@LOOP
	D;JLE
	@counter
	M=D
	@R0
	D=M
	@R2
	M=D
(LOOP)
	@counter
	MD=M-1
	@LOOP
	D;JLE
	@R0
	D=M
	@R2
	M=D+M
	@LOOP
	0;JMP
(INFINITE_LOOP)
	@LOOP
	0;JMP
