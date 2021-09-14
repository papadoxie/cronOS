%define MULTIBOOT_HEADER_MAGIC 0x1BADB002   /* Multiboot header magic number */
%define MULTIBOOT_HEADER_FLAGS 0x00000003   /* Multiboot header flags */
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS) /* Multiboot header checksum */


global _start, _kmain
extern kmain, start_ctors, end_ctors, start_dtors, end_dtors

_start:
    jmp start

; Load the multiboot header
align 4

multiboot_header:
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd CHECKSUM

start:
    push ebx

; Call static constructors
static_ctors_loop:
    mov ebx, start_ctors    ; Get the address of the start of the list
    jmp .test

.body:
    call [ebx]            ; Call the constructor
    add ebx, 4

.test:
    cmp ebx, end_ctors  ; Check if we've reached the end of the list
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


cli     ; Disable interrupts
hlt     ; Halt the CPU