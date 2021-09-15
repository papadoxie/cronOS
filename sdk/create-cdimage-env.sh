#!/bin/bash

mkdir ../kernel/$(BIN_DIR)/iso
mkdir ../kernel/$(BIN_DIR)/iso/boot
mkdir ../kernel/$(BIN_DIR)/iso/boot/grub

cp ../sdk/grub.cfg $(BIN_DIR)/iso/boot/grub/grub.cfg
