# Directories
SOURCE_DIR = source
INCLUDE_DIR = include
ARCH_SOURCE = arch/$(ARCH)/source
ARCH_INCLUDE = arch/$(ARCH)/include
KERNEL_INCLUDE = ../arch/$(ARCH)/include
BIN_DIR = bin

# Assembler Settings
AS = nasm
ASFLAGS = -f elf

# Linker Settings
LINKER = ld
LDFLAGS = -melf_i386 -nostdlib -r
LDFLAGS := $(LDFLAGS) -L$(INCLUDE_DIR)
LINK_SCRIPT =

# C Compiler Settings
CC = gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE)
CFLAGS := $(CFLAGS) -m32
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding -fno-stack-protector

# Files
## Sources
C_SRCS = $(wildcard $(SOURCE_DIR)/**/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)
ARCH_C_SRCS = $(wildcard $(ARCH_SOURCE)/*.c)
ARCH_ASM_SRCS = $(wildcard $(ARCH_SOURCE)/*.asm)
## Objects
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ = $(BIN_DIR)/crti.o
CRTN_OBJ = $(BIN_DIR)/crtn.o
ARCH_C_OBJS = $(patsubst $(ARCH_SOURCE)/%.c, $(BIN_DIR)/%.o, $(ARCH_C_SRCS))
ARCH_ASM_OBJS = $(patsubst $(ARCH_SOURCE)/%.asm, $(BIN_DIR)/%.o, $(ARCH_ASM_SRCS))
C_OBJS_NODIR = $(notdir $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS)))
C_OBJS = $(foreach cobj, $(C_OBJS_NODIR), $(addprefix $(BIN_DIR)/, $(cobj)))
ASM_OBJS = $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))
## Object Linked List
OBJS = $(ARCH_C_OBJS) $(ARCH_ASM_OBJS) $(C_OBJS) $(ASM_OBJS)
OBJS := $(filter-out $(CRTI_OBJ), $(OBJS))
OBJS := $(filter-out $(CRTN_OBJ), $(OBJS))


BIN = $(BIN_DIR)/libk.a

.PHONY: all clean

all: $(BIN_DIR) $(BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN): $(OBJS)
	@echo -e "OBJECTS = $(OBJS)\n"
	$(LINKER) $(LDFLAGS) $(LINK_SCRIPT) $(OBJS) -o $@
	$(RM) $(BIN_DIR)/!\(crt\)*.o

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(C_SRCS)
	$(CC) $(CFLAGS) -c $< -o $(BIN_DIR)/$(notdir $@)

clean:
	$(RM) -r $(BIN_DIR)