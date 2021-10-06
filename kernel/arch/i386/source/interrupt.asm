section .rodata
    IRQ_BASE equ 0x20

section .data
    interrupt_number db 0

section .text
    extern __handle_interrupt

    %macro exception_handler number
        global exception_handler_$number
        mov $number, BYTE [interrupt_number]
        jmp int_bottom
    %endmacro

    %macro ireq_handler number
        global __ireq_handler_$number
        mov $number, BYTE [interrupt_number]
        jmp int_bottom
    %endmacro

    ireq_handler 0x00
    ireq_handler 0x01

    int_bottom:
        pusha
        push ds
        push es
        push fs
        push gs

        push esp
        push BYTE [interrupt_number]
        call __handle_interrupt
        mov esp, eax

        pop gs
        pop fs
        pop es
        pop ds
        popa

        iretd