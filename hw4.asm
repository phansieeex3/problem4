.ORIG x3000
LEA R1, MEMORY
LEA R0, PROMPT1
PUTS
LOOP:
	LEA R0, MEMORY
        GETC ;input character 
	STR R0, R1, #0 ;put this in my memory block
	ADD R1, R1, #1 ;increment the memory pointer
        AND R2, R2, #0
        ADD R2, R2, R0 ; Use R2 to check for Newline (0x0A)
        ADD R2, R2, #-10 ; 0 if char is Newline
        BRnp LOOP ; If R2 is not Newline loop;
ADD R1, R1, #-1
STR R2, R1, #0 ;put this in my memory block
LEA R0, PROMPT2
PUTS
GETC
; -> Go to Sub Routine
LEA R0, MEMORY
PUTS
HALT
SALT .FILL #3
PROMPT1 .STRINGZ "Please enter your name."
PROMPT2 .STRINGZ "\nPress any key to continue: "
MEMORY .BLKW #20
.END