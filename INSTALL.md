## Dependencies for building the OS

- make
- build-essential (base-devel on Arch Linux)
- qemu
- grub (On WSL you need to compile this from source)
- qemu-arch-extra
- xorriso
- nasm 
- mtools

## Compilation
The project uses a recursive make setup  
Kernel can be compiled separately or with the whole project

+ List all the supported targets  
`make help`

+ Set required environment variables (by default ARCH is set to i386)  
`set ARCH=[ i386 | amd64 ]`

+ Build all the binaries  
`make all`

+ Create a bootable iso  
`make cdimage`  
You might need to compile grub yourself if you get missing file errors during this  

+ Clean up all the built files including the iso  
`make clean`

### Compiling the kernel seperately
+ You need to set ARCH manually even in the case of i386 (libk can also be compiled the same way)  
`make all ARCH=[ i386 | amd64 ]`