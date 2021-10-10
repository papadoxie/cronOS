## Operating System

Trying to write my own operating system from scratch

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