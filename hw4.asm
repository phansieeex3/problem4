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

LEA R1, MEMORY ;load beggining address of my array.
LD R2, SALT ;load small constant
LEA R3, ENCRYPT ;load start address of sub-routine
JSRR R3; -> Go to Encrypt 

PUTS ; Print results from Encrypt 
HALT
SALT .FILL #-3
PROMPT1 .STRINGZ "Please enter your name."
PROMPT2 .STRINGZ "\nPress any key to continue: "
MEMORY .BLKW #20

; ENCRYPT Subroutine
; Adds a small constant to each letter of a string
; R0 - Return value, start of string if successful
; R1 - Start address of string to proccess
; R2 - Small constant to add to each char
ENCRYPT AND R0, R0, #0
        ADD R0, R0, R1
        ST R3, SAVEDR3    
LOOP2	LDR R3, R0, #0 ;Load first char into R3 
	BRz END ;End Loop if char is end of string 0x00
        ADD R3, R3, R2 ; subtract R3 with salt
	STR R3, R0, #0 ;Save new char into memory
	ADD R0, R0, #1 ;increment 
	LDR R3, R0, #0 ;Load next char into R3
	BRnzp LOOP2 ; Proccess next char
END     AND R0, R0, #0
        ADD R0, R0, R1 ; Return starting address on success
        LD R3 SAVEDR3 ; Restore R3 register for caller
        RET

SAVEDR3 .FILL 0

.END