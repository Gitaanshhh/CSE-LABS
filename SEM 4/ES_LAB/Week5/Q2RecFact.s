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
	MOV R2, #1

recur	
	BL fact
	CMP R1, #0
	BEQ exit
	B recur

exit
	LDR R5, =FACT
	STR R2, [R5]
	B stop

fact
	MUL R2, R2, R1
	SUB R1, #1
	CMP R1, #0
	BNE fact
	BX LR

stop
	B stop

N DCD 3
	AREA mydata, DATA, READWRITE
FACT DCD 1
	END
