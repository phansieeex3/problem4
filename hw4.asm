.ORIG x3000
LEA R1, MEMORY
LOOP:
	GETC ;input character 
	STR R0, R1, #0 ;put this in my memory block
	ADD R1, R1, #1 ;increment the memory pointer
	BR LOOP
MEMORY .BLKW #20
.END