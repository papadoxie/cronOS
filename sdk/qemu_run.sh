#!/usr/bin/env bash

qemu-system-$AARCH \
-boot d \
-cdrom $KISO \
-m 512 \
-s -S \
&