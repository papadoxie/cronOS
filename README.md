## Operating System

Trying to write my own operating system from scratch

### Directory Structure (Will be updated as changes happen)
<pre>
kernel
    |_ arch
        |_ x86
        |   |_ bin
        |   |_ include
        |   |_ source
        |
        |_ x86_64
            |_ bin  
            |_ include
            |_ source
sdk
userland
</pre>

### Compilation
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

+ Clean up all the built files  
`make clean`