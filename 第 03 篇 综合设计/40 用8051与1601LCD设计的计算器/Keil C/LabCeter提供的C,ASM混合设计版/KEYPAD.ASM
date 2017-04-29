
/*******************************************************************************
************                 LABCENTER ELECTRONICS                  ************                              
************		Proteus VSM Sample Design Code                  ************		 	
************	       Integer Calculator ( 2K Code Limit)	        ************
*******************************************************************************/

NAME    KEYPAD
; This routine will read a character press from the keypad and return it in R7.

;Set up Segments for the Input Routine - No parameters.
?PR?input?KEYPAD               SEGMENT CODE
	PUBLIC	input
?DT?input?KEYPAD               SEGMENT DATA

RSEG  ?DT?input?KEYPAD                          ; Local Variable Segment for Output Routine.

KEY_ROW1	equ	0EFh
KEY_ROW2	equ	0DFh
KEY_ROW3	equ	0BFh
KEY_ROW4	equ	07Fh

keyflags:	ds	16

RSEG  ?PR?input?KEYPAD                          ; Code Segment for Output Routine.
input:

keyscan:push DPH
		push DPL
		
		mov R0,#keyflags 		; R0 addresses the key toggle bytes
		mov R1,#KEY_ROW1		; R1 address the keyboard row address
		mov R2,#4			; R2 counts rows
ksrow:	mov P2,R1			; Set row address to port P2
		nop
		mov A,P1			; Read column data from port P1
		mov R3,#4			; R3 counts keys per row
		anl A,#3Fh
ks0:	rrc A				; Move next bit into carry
		mov R4,A			; R4 preserves the row data
		jc ks1				; Jump if key not pressed
		mov A,@R0			; Test if key already pressed
		mov @R0,#1			; Flag pressed anyway
		jz ksnew			; Jump if key newly pressed
		jmp ks2
ks1:	mov @R0,#0			; Flag key as not pressed
ks2:	inc R0				; Loop for next key in this row
		mov A,R4
		djnz R3,ks0

		mov A,R1			; Jiggle R1 to address next row
		rl A 
		mov R1,A
		djnz R2,ksrow

		clr A				
		mov R7,A			; Return zero - no (new) key press.	
		jmp ksend
						
ksnew:	mov DPTR,#keycodes		; We've found a new key since last time:
		mov A,R0			; The key flag address (ordinal) is in R0
		clr C
		subb A,#keyflags
		movc A,@A+DPTR
		mov R7,A			; Move the Key into R7 to be returned.
ksend:	mov P2,#0FFh
		pop DPL
		pop DPH
		ret

;Data tables for returned row bits
keycodes:
        db 	'7','8','9', '/'
		db	'4','5','6', '*'
		db	'1','2','3', '-'
		db	'C','0','=', '+'

		END
