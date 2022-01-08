section .rodata
    MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002                                          ; Multiboot header magic number
    MULTIBOOT_HEADER_ALIGN  equ 1 << 0                                              ; Alignment of multiboot header
    MEMINFO                 equ 1 << 1                                              ; Memory map information
    MULTIBOOT_HEADER_FLAGS  equ (MULTIBOOT_HEADER_ALIGN | MEMINFO)                  ; Multiboot header flags
    CHECKSUM                equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)  ; Multiboot header checksum

    KERNEL_SSIZE            equ 0x4000                                              ; Kernel stack size (16 KiB)

;------------------------------------------------------------------------------

section .multiboot
align 4
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
        mov esp, kernel_stackptr    ; Set up kernel stack
        push eax                    ; Pass the multiboot magic number to kmain
        push ebx                    ; Pass the multiboot header to kmain

    ; Call static constructors (redundant after crti)
    static_ctors_loop:
        mov ebx, start_ctors        ; Get the address of the start of the list 
        jmp .test

        .body:
            call [ebx]              ; Call the constructor 
            add ebx, 4

        .test:
            cmp ebx, end_ctors      ; Check if we've reached the end of the list 
            jb .body

    ; Call kernel main
    call kmain

    ; Call static destructors (redundant after crtn)
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
; Create kernel stack pointer
align 16
    resb KERNEL_SSIZE ; 16KiB of kernel stack
    kernel_stackptr:
