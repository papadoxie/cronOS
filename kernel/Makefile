AS = as
ASFLAGS = --32

LINKER = ld
LDFLAGS = -melf_i386

CC = gcc
CFLAGS = -m32 -Wall -Werror -fno-exceptions -fno-builtin

SOURCE_DIR = arch/$(ARCH)/source
INCLUDE_DIR = arch/$(ARCH)/include
BIN_DIR = arch/$(ARCH)/bin

C_SRCS = $(wildcard $(SOURCE_DIR)/*.c)
ASM_SRCS += $(wildcard $(SOURCE_DIR)/*.asm)
HDRS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJS = $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))
OBJS += $(patsubst $(SOURCE_DIR)/%.asm, $(BIN_DIR)/%.o, $(ASM_SRCS))

BIN = $(BIN_DIR)/kernel.bin

all: $(BIN)

$(BIN): $(OBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BIN_DIR)/*