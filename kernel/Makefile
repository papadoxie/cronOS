# Kernel Libraries
LIBK =  libk
LIBK_HDRS = $(LIBK)/include
LIBK_BIN = $(LIBK)/bin

# Directories
SOURCE_DIR = arch/$(ARCH)/source
INCLUDE_DIR = arch/$(ARCH)/include
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
CFLAGS := -I$(LIBK_HDRS) -I$(INCLUDE_DIR)
CFLAGS := $(CFLAGS) -m32 -nostdinc
CFLAGS := $(CFLAGS) -Wall -Werror
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding

# Files
## Sources
C_SRCS = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)
## Headers
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)
## Objects
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ = $(LIBK_BIN)/crti.o
CRTN_OBJ = $(LIBK_BIN)/crtn.o
OBJS := $(CRTI_OBJ) $(CRTBEGIN_OBJ)
OBJS := $(OBJS) $(wildcard $(LIBK_BIN)/*.o)
OBJS := $(filter-out $(LIBK_BIN)/crti.o, $(OBJS))
OBJS := $(filter-out $(LIBK_BIN)/crtn.o, $(OBJS))
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))
OBJS := $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

# Kernel Binary
BIN = $(BIN_DIR)/kernel.bin

# Targets
.PHONY: all clean

all: $(BIN_DIR) $(BIN)
cdimage: $(ISO)

$(ISO): $(BIN) 
	cp $< ../iso/boot/kernel.bin

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN): $(OBJS)
	$(LINKER) $(LDFLAGS) $(LINK_SCRIPT) $^ -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBK)
	$(RM) -r $(BIN_DIR)