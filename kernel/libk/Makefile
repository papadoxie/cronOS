#! Directories
SOURCE_DIR = source
INCLUDE_DIR = include
ARCH_SOURCE = arch/$(ARCH)/source
ARCH_INCLUDE = arch/$(ARCH)/include
KERNEL_INCLUDE = ../arch/$(ARCH)/include
BIN_DIR = bin


#! Assembler Settings
AS = nasm
ASFLAGS = -f elf


#! Linker Settings
LINKER = ld
LDFLAGS = -melf_i386 -nostdlib -r
LDFLAGS := $(LDFLAGS) -L$(INCLUDE_DIR)
LINK_SCRIPT =


#! C Compiler Settings
CC = gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR) -I$(KERNEL_INCLUDE)
CFLAGS := $(CFLAGS) -m32
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra -Wpedantic
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding -fno-stack-protector


#! Files
##? Sources
C_SRCS = $(wildcard $(SOURCE_DIR)/**/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)
ARCH_C_SRCS = $(wildcard $(ARCH_SOURCE)/*.c)
ARCH_ASM_SRCS = $(wildcard $(ARCH_SOURCE)/*.asm)

##? Objects
### C Runtime
CRTI_OBJ = $(BIN_DIR)/crti.o
CRTN_OBJ = $(BIN_DIR)/crtn.o
CRT_OBJS = $(CRTI_OBJ) $(CRTN_OBJ)

### Architecture Specific
ARCH_C_OBJS = $(patsubst $(ARCH_SOURCE)/%.c, $(BIN_DIR)/%.o, $(ARCH_C_SRCS))
ARCH_ASM_OBJS = $(patsubst $(ARCH_SOURCE)/%.asm, $(BIN_DIR)/%.o, $(ARCH_ASM_SRCS))

### General
C_OBJS_NODIR = $(notdir $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS)))
C_OBJS = $(foreach cobj, $(C_OBJS_NODIR), $(addprefix $(BIN_DIR)/, $(cobj)))
ASM_OBJS = $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))

## Object Linked List
OBJS = $(ARCH_C_OBJS) $(ARCH_ASM_OBJS) $(C_OBJS) $(ASM_OBJS)


##? Binary
BIN = $(BIN_DIR)/libk.a

#! Targets
.PHONY: all clean

all: $(BIN_DIR) $(BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN): $(OBJS)
# Don't want CRT Objects in libk since they will be linked to kernel anyways
	$(LINKER) $(LDFLAGS) $(LINK_SCRIPT) $(filter-out $(CRT_OBJS), $(OBJS)) -o $@
# No need for seperate objects after libk.a is created
	$(RM) $(filter-out $(CRT_OBJS), $(OBJS))

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%.o: $(ARCH_SOURCE)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/**/%.c
	$(CC) $(CFLAGS) -c $< -o $(BIN_DIR)/$(notdir $@)

clean:
	$(RM) -rv $(BIN_DIR)