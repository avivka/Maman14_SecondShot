; file test2.as

.entry LIST
.extern W
.define sz = 2
MAIN:	mov r3, LIST[sz]
LOOP:	jmp W
		prn #-5
		sub r1, r4
		mov STR[5], STR[2]
		cmp K, #sz
		bne W
		L1:	inc L3
.entry LOOP
		bne LOOP
END:	stop
.define len = 4
STR: .string "abcdef"
LIST: .data 6, -9, len
K: .data 22
.extern L3

;[forum] fix for solution in line 108 00000000101000 --> ****%%*
;[forum] fix for solution in line 117 00000000001000 --> *****%*
