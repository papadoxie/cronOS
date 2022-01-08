#!/usr/bin/env bash

if [ "$DDEBUG" == "1" ] 
then
    qemu-system-$AARCH \
    -boot d \
    -cdrom $KISO \
    -m 512 \
    -s -S \
    &

    gdb kernel/bin/kernel.bin \
    -ex "target remote :1234" \
    -ex "break _start" \
    -ex "continue" \

else 
    qemu-system-$AARCH \
    -boot d \
    -cdrom $KISO \
    -m 512 \
    &
fi

