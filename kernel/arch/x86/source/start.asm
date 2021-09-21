section .rodata
    MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002                                          ; Multiboot header magic number
    MULTIBOOT_HEADER_FLAGS  equ (1<<0 | 1<<1)                                       ; Multiboot header flags
    CHECKSUM                equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)  ; Multiboot header checksum

;------------------------------------------------------------------------------

section .multiboot
    dd MULTIBOOT_HEADER_MAGIC    
    dd MULTIBOOT_HEADER_FLAGS    
    dd CHECKSUM

;------------------------------------------------------------------------------

section .text
    global _start, _kmain
    extern kmain
    extern start_ctors, end_ctors
    extern start_dtors, end_dtors

    _start:
        mov esp, kernel_stackptr
        push eax
        push ebx

    ; Call static constructors
    static_ctors_loop:
        mov ebx, start_ctors    ; Get the address of the start of the list 
        jmp .test

    .body:
        call [ebx]              ; Call the constructor 
        add ebx, 4

    .test:
        cmp ebx, end_ctors      ; Check if we've reached the end of the list 
        jb .body

    ; Call kernel main
    call kmain

    ; Call static destructors
    static_dtors_loop:
        mov ebx, start_dtors    ; Get the address of the start of the list 
        jmp .test

        .body:
            call [ebx]          ; Call the destructor 
            add ebx, 4

        .test:
            cmp ebx, end_dtors  ; Check if we've reached the end of the list 
            jb .body


    _stop:          ; This is the end of the program 
        cli         ; Disable interrupts 
        hlt         ; Halt the CPU 
        jmp _stop

;------------------------------------------------------------------------------

section .bss
    resw 2*1024*1024
    kernel_stackptr:
