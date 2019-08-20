; 3.as example of error
MAIN: mov r3 , LENGTH
prn #-5
bne LOOP(r4,r5)
sub r1, r6
bne END
L1: inc K
bne LOOP(K,STR)
END:    stop #1
sub r1, #5
STR: .string "ancdef"
123: .string "abcd"
r5: .string "abcd"
jmp: r1, #5
LENGTH:  .data 6,-9,15
K:             .data 22

    .entry K