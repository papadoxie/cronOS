AS = nasm
ASFLAGS = -f elf

LINKER = ld
LDFLAGS = -melf_i386
LINK_SCRIPT = -T $(SOURCE_DIR)/linker.ld

CC = gcc
CFLAGS = -m32 -Wall -Werror -fno-exceptions -fno-builtin

SOURCE_DIR = arch/$(ARCH)/source
INCLUDE_DIR = arch/$(ARCH)/include
BIN_DIR = bin

C_SRCS = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRCS = $(wildcard $(SOURCE_DIR)/*.asm)
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))
OBJS += $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))

BIN = $(BIN_DIR)/kernel.bin

.PHONY: clean

all: $(BIN_DIR) $(BIN)
cdimage: $(ISO)

$(ISO): $(BIN)
	cp $< ../iso/boot/kernel.bin

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN): $(OBJS)
	$(LINKER) $(LDFLAGS) $(LINK_SCRIPT) $(OBJS) -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN_DIR)