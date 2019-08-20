; 1.asm
add  X, r4
y: .data 7


L1: mov y,r3
X: .data 10,-3
mov  #4, Z
jmp L1(#-5,y)
   .entry y
mov #3,Z

   .extern Z