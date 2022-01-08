NAME = CustomOS
VERSION = 0.1.0-papadoxie
# Default architecture
ARCH = i386

SDK_DIR = sdk
KERNEL_DIR = kernel
KERNEL_LIB_DIR = ${KERNEL_DIR}/libk
USERLAND_DIR = userland
SYSROOT = sysroot
BIN_DIR = bin
ISO = $(BIN_DIR)/$(NAME)-$(VERSION).iso

# Colors for colored output
BLUE = \033[0;34m
GREEN =\033[0;32m
NC = \033[0m

.PHONY: clean run help cdimage

help:
	@echo "Makefile for building Operating System."
	@echo "Usage: make [ all | cdimage | clean | help | build | run ] ARCH=[ i386 | amd64 ]"

all: $(BIN_DIR)
	@echo -e "$(BLUE)Building Kernel Libraries...$(NC)"
	$(MAKE) -C $(KERNEL_LIB_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building Kernel Libraries Done$(NC)\n"
	@echo -e "$(BLUE)Building Kernel...$(NC)"
	$(MAKE) -C $(KERNEL_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building Kernel Done$(NC)\n"
	@echo -e "$(BLUE)Building SDK...$(NC)"
	$(MAKE) -C $(SDK_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building SDK Done$(NC)\n"
	@echo -e "$(BLUE)Building Userland...$(NC)"
	$(MAKE) -C $(USERLAND_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building Userland Done$(NC)\n"

$(BIN_DIR):
	mkdir $(BIN_DIR)

build:
	zip -r OS-$(VERSION).zip ./

cdimage: export ROOT = $(SYSROOT)
cdimage: export SDK = $(SDK_DIR)
cdimage: export OSNAME = $(NAME)
cdimage: export VERSIONN = $(VERSION)
cdimage: $(ISO)

$(ISO): $(SYSROOT)
	@echo -e "\n$(BLUE)Building ISO Image...$(NC)"	
	grub-mkrescue $< -o $@
	@echo -e "$(GREEN)Building ISO Image Done$(NC)"
	@echo -e "$(BLUE)Cleaning up temporary files...$(NC)"
	$(RM) -rv $(SYSROOT)
	@echo -e "$(GREEN)Done!$(NC)"

$(SYSROOT): all
	@echo -e "\n$(BLUE)Creating OS Directory Structure...$(NC)"
	sdk/create-cdimage-env.sh
	@echo -e "$(GREEN)OS Directory Structure Created$(NC)"
	$(MAKE) cdimage -C $(KERNEL_DIR) ARCH=$(ARCH)

run: export AARCH = $(ARCH)
run: export KISO = $(ISO)
run:
	@echo "Running Operating System..."
	@sdk/qemu_run.sh

clean:
	@echo -e "$(BLUE)Cleaning up...$(NC)"
	$(RM) -rv $(BIN_DIR)
	$(MAKE) -C $(KERNEL_DIR) clean
	$(MAKE) -C $(KERNEL_LIB_DIR) clean
	$(MAKE) -C $(SDK_DIR) clean
	$(MAKE) -C $(USERLAND_DIR) clean
	$(RM) -rv $(SYSROOT)