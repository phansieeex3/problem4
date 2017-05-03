.ORIG x3000
     LEA R1, MEMORY
     LEA R0, PROMPT1
     PUTS

LOOP GETC             ; input character
     OUT              ; echo user input 
     STR R0, R1, #0   ; put this in my memory block
     ADD R1, R1, #1   ; increment the memory pointer
     ADD R0, R0, #-10 ; 0 if char is Newline
     BRnp LOOP        ; If R2 is not Newline loop

     ADD R1, R1, #-1
     STR R0, R1, #0   ; put this in my memory block
     LEA R1, MEMORY   ; load beggining address of my array.
     LD  R2, SALT     ; load small constant
     LEA R3, ENCRYPT  ; load start address of sub-routine
     JSRR R3          ; -> Go to Encrypt 
     NOT R1, R1
     ADD R1, R1, #1
     ADD R1, R1, R0   ; Check for correct return value, expects same address as R1
     BRnp ERR
     LEA R0, PROMPT2
     PUTS
     GETC
     LEA R0, MEMORY
     PUTS             ; Print results from Encrypt 
     BRnzp DONE
ERR  LEA R0 ERROR
     PUTS             ; Print error message
DONE HALT

MEMORY  .BLKW    #20
SALT    .FILL    #-3
PROMPT1 .STRINGZ "Please enter your first name: "
PROMPT2 .STRINGZ "Press any key to continue: "
ERROR   .STRINGZ "Error occurred in Encrypt, halting program."

; ENCRYPT Subroutine
; Adds a small constant to each letter of a string
; R0 - Return value, start of string if successful
; R1 - Start address of string to proccess
; R2 - Small constant to add to each char
; Only R0 will be changed

ENCRYPT AND R0, R0, #0
        ADD R0, R0, R1
        ST R3, SAVEDR3    

LOOP2	LDR R3, R0, #0 ; Load first char into R3 
	BRz END        ; End Loop if char is end of string 0x00
        ADD R3, R3, R2 ; subtract R3 with salt
	STR R3, R0, #0 ; Save new char into memory
	ADD R0, R0, #1 ; increment 
	BRnzp LOOP2    ; Proccess next char

END     AND R0, R0, #0
        ADD R0, R0, R1 ; Return starting address on success
        LD R3 SAVEDR3  ; Restore R3 register for caller
        RET

SAVEDR3 .FILL 0

.END