NAME = CustomOS
VERSION = 0.1.0-papadoxie

SDK_DIR = ./sdk
KERNEL_DIR = ./kernel
USERLAND_DIR = ./userland
ISO_DIR = ./iso

help:
	@echo "Makefile for building Operating System."
	@echo "Usage: make [ all | cdimage | clean | help | build | run ] ARCH=[ x86 | x86_64 ]"

all:
	@echo "Building Kernel"
	make -C $(KERNEL_DIR) ARCH=$(ARCH)
	@echo "Building Kernel Done"
	@echo "Building SDK"
	make -C $(SDK_DIR) ARCH=$(ARCH)
	@echo "Building SDK Done"
	@echo "Building Userland"
	make -C $(USERLAND_DIR) ARCH=$(ARCH)
	@echo "Building Userland Done"

build:
	zip -r OS-$(VERSION).zip ./

cdimage: export ISO = $(ISO_DIR)
cdimage: export SDK = $(SDK_DIR)
cdimage:
	@echo "Building ISO Image..."
	sdk/create-cdimage-env.sh
	make cdimage -C $(KERNEL_DIR) ARCH=$(ARCH)
	grub-mkrescue -d $(ISO_DIR) -o $(NAME)-$(VERSION).iso
	@echo "Building ISO Image Done"
	@echo "Cleaning up..."
	$(RM) -r $(ISO_DIR)

run:
	@echo "Running Operating System..."
	cd $(SDK_DIR) && sudo bash ./diskimage.sh
	cd $(SDK_DIR) && ./qemu.sh

clean:
	@echo "Cleaning up..."
	make -C $(KERNEL_DIR) clean
	make -C $(SDK_DIR) clean
	make -C $(USERLAND_DIR) clean
	$(RM) -r $(ISO_DIR)