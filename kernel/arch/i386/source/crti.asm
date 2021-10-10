; x86 ctri.asm

section .init
    global _init
    type _init, @function

    _init:
        push ebp
        mov ebp, esp
        ; CC Insert here

section .fini
    global _fini
    type _fini, @function

    _fini:
        push ebp
        mov ebp, esp
        ; CC Insert here
