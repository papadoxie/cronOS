NAME = CustomOS
VERSION = 0.1.0-papadoxie
# Default architecture
ARCH = i386

SDK_DIR = ./sdk
KERNEL_DIR = ./kernel
USERLAND_DIR = ./userland
ISO_DIR = ./iso
BIN_DIR = ./bin
ISO = $(BIN_DIR)/$(NAME)-$(VERSION).iso

help:
	@echo "Makefile for building Operating System."
	@echo "Usage: make [ all | cdimage | clean | help | build | run ] ARCH=[ i386 | amd64 ]"

all: $(BIN_DIR)
	@echo "Building Kernel"
	make -C $(KERNEL_DIR) ARCH=$(ARCH)
	@echo "Building Kernel Done"
	@echo "Building SDK"
	make -C $(SDK_DIR) ARCH=$(ARCH)
	@echo "Building SDK Done"
	@echo "Building Userland"
	make -C $(USERLAND_DIR) ARCH=$(ARCH)
	@echo "Building Userland Done"

$(BIN_DIR):
	mkdir $(BIN_DIR)

build:
	zip -r OS-$(VERSION).zip ./

cdimage: export ISO = $(ISO_DIR)
cdimage: export SDK = $(SDK_DIR)
cdimage: export OSNAME = $(NAME)
cdimage: export VERSIONN = $(VERSION)
cdimage: $(ISO)

$(ISO): $(ISO_DIR)
	@echo "Building ISO Image..."	
	grub-mkrescue $< -o $@
	@echo "Building ISO Image Done"
	@echo "Cleaning up temporary files..."
	$(RM) -r $(ISO_DIR)
	@echo "Done!"

$(ISO_DIR): all
	sdk/create-cdimage-env.sh
	make cdimage -C $(KERNEL_DIR) ARCH=$(ARCH)

run:
	@echo "Running Operating System..."
	@qemu-system-$(ARCH) -boot d -cdrom $(ISO) -m 512 &

clean:
	@echo "Cleaning up..."
	$(RM) -r $(BIN_DIR)
	make -C $(KERNEL_DIR) clean
	make -C $(SDK_DIR) clean
	make -C $(USERLAND_DIR) clean
	$(RM) -r $(ISO_DIR)