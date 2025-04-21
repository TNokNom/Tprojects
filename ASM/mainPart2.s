
.global _start
.section .data

Sue: .word 0x98765432, 0xabcdefed, 0x12345678
Joe: .word 0x8987dcba, 0xaaaa1237, 0xbbbbeeee
Ann: .word 0xba345678, 0x1ef67edc, 0x1f2bcab0
Bob: .space 12

.section .text
_start:
    LDR R1, =Sue
    LDR R2, [R1]
    LDR R3, [R1, #4]
    LDR R4, [R1, #8]

    LDR R5, =Joe
    LDR R6, [R5]
    LDR R7, [R5, #4]
    LDR R8, [R5, #8]

    LDR R9, =Ann
    LDR R10, [R9]
    LDR R11, [R9, #4]
    LDR R12, [R9, #8]

    ADDS R2, R2, R6
    ADCS R3, R3, R7
    ADCS R4, R4, R8
    SUBS R2, R2, R10
    SBCS R3, R3, R11
    SBCS R4, R4, R12

    LDR R0, =Bob
    STR R2, [R0]
    STR R3, [R0, #4]
    STR R4, [R0, #8]

end_program:
    B end_program
