SDK_DIR = ./sdk
KERNEL_DIR = ./kernel
USERLAND_DIR = ./userland

help:
	@echo "Makefile for building Operating System."
	@echo "Usage: make [ all | clean | help | build | run ] ARCH=[ x86 | x86_64 ]"

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

run:
	@echo "Running Operating System..."
	cd $(SDK_DIR) && sudo bash ./diskimage.sh
	cd $(SDK_DIR) && ./qemu.sh

clean:
	make -C $(KERNEL_DIR) clean
	make -C $(SDK_DIR) clean
	make -C $(USERLAND_DIR) clean