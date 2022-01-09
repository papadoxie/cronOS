#!/bin/bash

# Sysroot
mkdir $ROOT

# Top level directories
mkdir $ROOT/bin
mkdir $ROOT/boot
mkdir $ROOT/lib
mkdir $ROOT/root
mkdir $ROOT/home
mkdir $ROOT/usr

# Boot Directory
mkdir $ROOT/boot/grub

echo -e "set timeout=0 \n\
set default=0 \n\
\n\
menuentry \"$OSNAME ver $VERSIONN\" { \n\
    multiboot /boot/kernel.bin \n\
    boot \n\
} \n" > $ROOT/boot/grub/grub.cfg

# USR
mkdir $ROOT/usr/lib
mkdir $ROOT/usr/bin
mkdir $ROOT/usr/sbin
mkdir $ROOT/usr/share
mkdir $ROOT/usr/include
