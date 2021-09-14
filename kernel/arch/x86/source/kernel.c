typedef void (*constructor)();
void puts(const char *str);

void kmain(void * multiboot_structure, unsigned int magicnumber)
{
    puts("This is a test of the operating system");
    for(int i = 0; i < __INT32_MAX__; i++)
    {
        asm volatile("nop");
    }
}

void puts(const char * str)
{
    unsigned short *vidmem = (unsigned short *)0xb8000;

    for (int i = 0; str[i] != '\0'; i++)
    {
        vidmem[i] = (vidmem[i] & 0xFF00) | str[i];
    }
}