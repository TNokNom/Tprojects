
.global _start
.section .text

_start:
    MOV R1, #12
    MOV R2, #34
    MOV R3, #56

    MOV R4, #10000
    MUL R1, R1, R4

    MOV R4, #100
    MUL R2, R2, R4

    ADD R0, R1, R2
    ADD R0, R0, R3


end_program:
    B end_program
