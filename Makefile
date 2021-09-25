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

# Colors for colored output
BLUE = \033[0;34m
GREEN =\033[0;32m
NC = \033[0m

help:
	@echo "Makefile for building Operating System."
	@echo "Usage: make [ all | cdimage | clean | help | build | run ] ARCH=[ i386 | amd64 ]"

all: $(BIN_DIR)
	@echo -e "$(BLUE)Building Kernel...$(NC)"
	make -C $(KERNEL_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building Kernel Done$(NC)\n"
	@echo -e "$(BLUE)Building SDK...$(NC)"
	make -C $(SDK_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building SDK Done$(NC)\n"
	@echo -e "$(BLUE)Building Userland...$(NC)"
	make -C $(USERLAND_DIR) ARCH=$(ARCH)
	@echo -e "$(GREEN)Building Userland Done$(NC)\n"

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
	@echo -e "\n$(BLUE)Building ISO Image...$(NC)"	
	grub-mkrescue $< -o $@
	@echo -e "$(GREEN)Building ISO Image Done$(NC)"
	@echo -e "$(BLUE)Cleaning up temporary files...$(NC)"
	$(RM) -r $(ISO_DIR)
	@echo -e "$(GREEN)Done!$(NC)"

$(ISO_DIR): all
	sdk/create-cdimage-env.sh
	make cdimage -C $(KERNEL_DIR) ARCH=$(ARCH)

run:
	@echo "Running Operating System..."
	@qemu-system-$(ARCH) -boot d -cdrom $(ISO) -m 512 &

clean:
	@echo -e "$(BLUE)Cleaning up...$(NC)"
	$(RM) -r $(BIN_DIR)
	make -C $(KERNEL_DIR) clean
	make -C $(SDK_DIR) clean
	make -C $(USERLAND_DIR) clean
	$(RM) -r $(ISO_DIR)