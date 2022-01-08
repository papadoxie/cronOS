# cronOS
## customizable reconfigurable opensource *nix Operating System

My attempt at writing an operating system from scratch

### Current Status:   
    Build: Passed ✔️
    Operations: Triple Fault on GDT Init (Bootloop) ❌


### Directory Structure (Will be updated as changes happen)
<pre>
kernel
    |_ arch
    |   |_ i386
    |   |   |_ bin
    |   |   |_ include
    |   |   |_ source
    |   |
    |   |_ amd64
    |       |_ bin  
    |       |_ include
    |       |_ source
    |_ libk
        |_ arch
        |   |_ i386
        |   |   |_ source
        |   |   |_ include
        |   |   
        |   |_ amd64
        |       |_ source
        |       |_ include
        |
        |_ source
        |_ include

sysroot
    |_ boot
    |_ bin
    |_ usr
    |_ lib
    |_ root
sdk
userland
</pre>

### <a href="INSTALL.md">Installation Instructions</a>
#### Note
Might not compile sometimes as I work on the code  
Depends on what Im working on before making commits  
I will make sure this doesn't happen once there is a proper release