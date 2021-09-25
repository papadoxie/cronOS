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

+ Set required environment variables  
`set ARCH=[ x86 | x86_64 ]`

+ Build all the binaries  
`make all`

+ Create a bootable iso  
`make cdimage`  
You might need to compile grub yourself if you get missing file errors during this  

+ Clean up all the built files  
`make clean`