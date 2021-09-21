#!/bin/bash

dd if=/dev/zero of=$OSNAME-$VERSIONN.iso bs=1048576 count=128

fdisk $OSNAME-$VERSIONN.iso << EOF
o
n
p
1
2048
+8M
t 1

EOF

fdisk -l -u c.img
losetup -o 32256 /dev/loop1 c.img

mke2fs /dev/loop1
mount /dev/loop1 /mnt
cp -R bootdisk/* /mnt/
umount /mnt/
