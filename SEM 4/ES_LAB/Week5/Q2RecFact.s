	AREA RESET, DATA, READONLY
	EXPORT __Vectors
__Vectors 
	DCD 0x10001000
	DCD Reset_Handler
	ALIGN
	AREA mycode, CODE, READONLY
	ENTRY
	EXPORT Reset_Handler

Reset_Handler
	LDR R0, =N
	LDR R1, [R0]
	MOV R2, #1	;r2->fact

recur	
	BL fact		;call the fact fn
	CMP R1, #0	; if r1 (or n) = 0, exit loop, else continue recur
	BEQ exit
	B recur

exit
	LDR R5, =FACT	;Load Fact address and store value then stop	
	STR R2, [R5]
	B stop

fact
	MUL R2, R2, R1		; R2 = R2*R! -> R1 = N
	SUB R1, #1	; N-=1
	CMP R1, #0	; if n==0 return else call fact (recursion)
	BNE fact
	BX LR

stop
	B stop

N DCD 3		;N = 3
	AREA mydata, DATA, READWRITE
FACT DCD 1	;Fact = 1
	END
