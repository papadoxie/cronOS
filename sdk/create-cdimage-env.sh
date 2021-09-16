#!/bin/bash

mkdir $ISO
mkdir $ISO/boot
mkdir $ISO/boot/grub

cp $SDK/grub.cfg $ISO/boot/grub/grub.cfg
