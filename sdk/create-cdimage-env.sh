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
cp $SDK/grub.cfg $ROOT/boot/grub/grub.cfg

# USR
mkdir $ROOT/usr/lib
mkdir $ROOT/usr/bin
mkdir $ROOT/usr/sbin
mkdir $ROOT/usr/share
mkdir $ROOT/usr/include
