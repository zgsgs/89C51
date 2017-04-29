
 /******************************************************************************
************                LABCENTER ELECTRONICS                   ************                              
************	         Proteus VSM Sample Design Code             ************		 	
************	        Integer Calculator ( 2K Code Limit)         ************
********************************************************************************/

NAME    LCD

;Set up Code Segment and exports:

LCD              SEGMENT CODE
RSEG             LCD

                 PUBLIC  _output
                 PUBLIC  initialise
                 PUBLIC  clearscreen

;LCD Register Addresses.
LCD_CMD_WR	equ 	00h
LCD_DATA_WR	equ	01h
LCD_BUSY_RD	equ	02h
LCD_DATA_RD	equ	03h
LCD_PAGE	equ	80h

;LCD Commands
LCD_CLS		equ	1
LCD_HOME	equ	2
LCD_SETMODE	equ	4
LCD_SETVISIBLE	equ	8
LCD_SHIFT	equ	16
LCD_SETFUNCTION	equ	32
LCD_SETCGADDR	equ	64
LCD_SETDDADDR	equ	128

; Initialisation Routine for the LCD display.
initialise: 
        mov A,#030h			;1 line, 8 bits
		call wrcmd
		mov A,#LCD_SETVISIBLE + 4
		call wrcmd
		mov A,#LCD_SETDDADDR+15		; Start at right hand side of the display
		call wrcmd
		mov A,#LCD_SETMODE + 3		; Automatic Increment - Display shift left.  
		call wrcmd
        ret

; We move the parameter (held in R7) into the Accumulator prior to writing it.
_output:mov A,R7	
		call wrdata
		ret


;Clears the LCD display and sets the initialisation conditions.
clearscreen:
        mov A,#LCD_CLS
		call wrcmd
		mov A,#LCD_SETDDADDR + 15
		call wrcmd
		ret	
		
;*****************************
;******** SUBROUTINES ********
;*****************************

;Sub routine to write command:
wrcmd:	mov P2,#LCD_PAGE
		mov R0,#LCD_CMD_WR
		movx @R0,A
		jmp wtbusy

; Subroutine to Write a Character to the LCD Display.
wrdata:	MOV P2,#LCD_PAGE				
		MOV R0,#LCD_DATA_WR
		MOV A,R7
		MOVX @R0,A

; Subroutine to wait for a busy clear.	
wtbusy:	MOV R1,#LCD_BUSY_RD
		MOVX A,@R1
		JB ACC.7,wtbusy
        ret

        END
