	AREA    FONCTIONS, CODE, READONLY


waitN 	PROC
		EXPORT waitN
		PUSH {R4}
		MOV R4,R0
BCL 	CMP R4,#0
		BEQ Sortie
		SUB R4,#1
		B BCL
Sortie	POP {R4}
		BX LR
		ENDP
		END