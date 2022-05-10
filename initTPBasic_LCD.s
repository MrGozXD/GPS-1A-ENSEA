taillePile      EQU     0x00000100
;--------------ZONE memoire PILE--------------------------------
			AREA	STACK, NOINIT, READWRITE, ALIGN=3
memPile		SPACE	taillePile ; Reserve un espace pour la pile
_SPinitial
			PRESERVE8
;--------------ZONE memoire RESET-------------------------------
; Vector Table Mapped to Address 0 at Reset
			AREA    RESET, DATA, READONLY
			EXPORT	__Vectors ;nom obligatoire
__Vectors	DCD     _SPinitial        ; Top of Stack
            DCD     Reset_Handler     ; Reset Handler
;--------------ZONE memoire CODE--------------------------------
			AREA    |.text|, CODE, READONLY
			ENTRY
; Reset Handler	
			EXPORT	Reset_Handler ;nom obligatoire
Reset_Handler	PROC

;insert your code here
     IMPORT  main
           LDR     R0, =main
           BX      R0
fin			B 	fin
			ENDP
			ALIGN
			END
;--------------FIN----------------------------------------------
