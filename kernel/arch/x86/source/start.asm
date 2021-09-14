.intel_syntax noprefix
.set MULTIBOOT_HEADER_MAGIC, 0x1BADB002   /* Multiboot header magic number */
.set MULTIBOOT_HEADER_FLAGS, 0x00000003   /* Multiboot header flags */
.set CHECKSUM, -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS) /* Multiboot header checksum */

/*------------------------------------------------------------------------------*/

.section .multiboot
    .long MULTIBOOT_HEADER_MAGIC    
    .long MULTIBOOT_HEADER_FLAGS    
    .long CHECKSUM

/*------------------------------------------------------------------------------*/

.section .text
    .global _start, _kmain
    .extern kmain
    .extern start_ctors, end_ctors
    .extern start_dtors, end_dtors
    
    _start:
        mov esp, kernel_stackptr
        push eax
        push ebx

    /* Call static constructors*/
    /*static_ctors_loop:
        mov ebx, start_ctors    /* Get the address of the start of the list*/
    /*    jmp .test

    .body:
        call [ebx]              /* Call the constructor*/
    /*    add ebx, 4

    .test:
        cmp ebx, end_ctors      /* Check if we've reached the end of the list*/
    /*    jb .body

    /* Call kernel main*/
    call kmain

    /* Call static destructors*/
    /*static_dtors_loop:
        mov ebx, start_dtors    /* Get the address of the start of the list*/
    /*    jmp .test02

        .body02:
            call [ebx]          /* Call the destructor*/
    /*        add ebx, 4

        .test02:
            cmp ebx, end_dtors  /* Check if we've reached the end of the list*/
    /*        jb .body02*/


    _stop:      /* This is the end of the program*/
        cli     /* Disable interrupts*/
        hlt     /* Halt the CPU*/
        jmp _stop

/*------------------------------------------------------------------------------*/

.section .bss
    .space 2*1024*1024
    kernel_stackptr:
