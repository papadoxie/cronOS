; x86 ctri.asm

section .init
    global _init

    _init:
        push ebp
        mov ebp, esp
        ; CC Insert here

section .fini
    global _fini

    _fini:
        push ebp
        mov ebp, esp
        ; CC Insert here
