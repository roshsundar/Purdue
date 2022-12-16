.global main
main:
    ldr x0, =0xABCDBEEFBAD1BAD0
    ldr x1, =0xEE10ACBD22433900
    ldr x2, =0x87874838217384FF

question_1:
    add x3, x0, x1

question_2:
    and x4, x0, x2
    eor x4, x4, x1

question_3:
    neg x5, x0
    orr x5, x5, x1
    and x5, x5, x2
    add x5, x5, x0

    ret
