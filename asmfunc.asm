; assembly part using x86-64

section .text
bits 64
default rel 
global asmFunc 

;extern float saxpy(int vectorSize, float* input1, float* input2, float multiplier); 
;// changed order so that vector size goes to rcx (first param)
;// rcx , [rdx], [r8], xmm3

asmFunc:
    
L1:
    movss xmm4, [rdx]
    mulss xmm4, xmm3
    addss xmm4, [r8]
    movss [rdx], xmm4
    
    add rdx, 4
    add r8, 4
    LOOP L1
    
    ret