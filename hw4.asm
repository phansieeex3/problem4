.ORIG x3000
LEA R1, MEMORY
AND R1, R1, #0
LOOP:
	GETC ;input character 
	STR R0, R1, #0 ;put this in my memory block
	ADD R1, R1, #1 ;increment the memory pointer
        AND R2, R2, #0
        ADD R2, R2, R0
        ADD R2, R2, #-10
	BRnp LOOP
PUTS
HALT
MEMORY .BLKW #20
.END