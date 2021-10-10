# Assembler Settings
AS = nasm
ASFLAGS = -f elf

# Linker Settings
LINKER = ld
LDFLAGS = -melf_i386 -nostdlib
LINK_SCRIPT = -T $(SOURCE_DIR)/linker.ld

# C Compiler Settings
CC = gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -m32
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding

SOURCE_DIR = source/
INCLUDE_DIR = include/