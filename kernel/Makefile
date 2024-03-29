#! Kernel Libraries
LIBK =  libk
LIBK_HDRS := $(LIBK)/include
LIBK_BIN := $(LIBK)/bin
LIB_NAMES := k

#! Directories
SOURCE_DIR := arch/$(ARCH)/source
INCLUDE_DIR := arch/$(ARCH)/include
LIB_DIRS := $(LIBK_BIN)/
BIN_DIR = bin

#! Assembler Settings
AS = nasm
ASFLAGS = -f elf

#! Linker Settings
LINKER = ld
LINK_DIRS := $(foreach libdir, $(LIB_DIRS), $(addprefix -L, $(libdir)))
LINK_ARCHIVES := $(foreach libdir, $(LIB_NAMES), $(addprefix -l, $(libdir)))
LDFLAGS := -melf_i386 -nostdlib -static 
LDPATH := $(LINK_DIRS) $(LINK_ARCHIVES)
LINK_SCRIPT := -T $(SOURCE_DIR)/linker.ld

#! C Compiler Settings
CC = gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -I$(LIBK_HDRS) -I$(INCLUDE_DIR)
CFLAGS := $(CFLAGS) -m32 -nostdinc
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra -Wpedantic
CFLAGS := $(CFLAGS) -fno-exceptions -fno-builtin -ffreestanding -fno-stack-protector
CFLAGS := $(CFLAGS) -MMD -MD -MP

#! Files
##? Sources
C_SRCS = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)

##? Objects
### C Runtime
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTI_OBJ = $(LIBK_BIN)/crti.o
CRTN_OBJ = $(LIBK_BIN)/crtn.o
CRT_LOCAL = $(CRTI_OBJ) $(CRTN_OBJ)

### Objects must be linked in this exact order
OBJS := $(CRTI_OBJ) $(CRTBEGIN_OBJ)
OBJS := $(OBJS) $(LIBK_BIN)/libk.a
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))
OBJS := $(OBJS) $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))
OBJS := $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

##? Headers
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
##? Dependencies
DEPS := $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.d, $(C_SRCS))

# Kernel Binary
BIN = $(BIN_DIR)/kernel.bin

# Targets
.PHONY: all clean

all: $(BIN_DIR) $(BIN) $(CRT_LOCAL)

cdimage: $(BIN)
	cp $< ../sysroot/boot/kernel.bin

$(CRT_LOCAL):
## Compiling the whole libk because we need it to build the kernel anyways
	$(MAKE) -C $(LIBK) all

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN): $(OBJS)
	$(LINKER) $(LDFLAGS) $(LINK_SCRIPT) $^ -o $@ $(LDPATH)

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rv $(BIN_DIR)