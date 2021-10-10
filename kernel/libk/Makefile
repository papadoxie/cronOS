# Directories
SOURCE_DIR = source
INCLUDE_DIR = include
ARCH_SOURCE = arch/$(ARCH)/source
ARCH_INCLUDE = arch/$(ARCH)/include
BIN_DIR = bin

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
CFLAGS := -I$(INCLUDE_DIR)
CFLAGS := $(CFLAGS) -m32
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding

# Files
## Sources
C_SRCS = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)
ARCH_C_SRCS = $(wildcard $(ARCH_SOURCE)/*.c)
ARCH_ASM_SRCS = $(wildcard $(ARCH_SOURCE)/*.asm)
## Objects
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ = $(BIN_DIR)/crti.o
CRTN_OBJ = $(BIN_DIR)/crtn.o
OBJS := $(CRTI_OBJ) $(CRTBEGIN_OBJ)
OBJS := $(OBJS) $(patsubst $(ARCH_SOURCE)/%.c, $(BIN_DIR)/%.o, $(ARCH_C_SRCS))
OBJS := $(OBJS) $(patsubst $(ARCH_SOURCE)/%.asm, $(BIN_DIR)/%.o, $(ARCH_ASM_SRCS))
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))
OBJS := $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: all clean

all: $(BIN_DIR) $(OBJS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN_DIR)