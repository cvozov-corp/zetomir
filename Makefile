ARCH := x86_64
CROSS ?= x86_64-elf-
CC := $(CROSS)gcc
LD := $(CROSS)ld
NASM := nasm
BUILD := build
ISO_ROOT := $(BUILD)/iso_root
LIMINE_DIR ?= limine
CFLAGS := -std=gnu11 -O2 -Wall -Wextra -Werror \
          -ffreestanding -fno-stack-protector -fno-pic -fno-pie \
          -m64 -mno-red-zone -mcmodel=kernel -mno-mmx -mno-sse \
          -mno-sse2 -I kernel
LDFLAGS := -m elf_x86_64 -nostdlib -static -z max-page-size=0x1000 -T linker.ld
C_SOURCES := $(shell find kernel -name '*.c')
OBJECTS := $(patsubst kernel/%.c,$(BUILD)/%.o,$(C_SOURCES))

.PHONY: all clean iso run debug limine test game zeto-check fetch browse
all: $(BUILD)/kernel.elf

test:
	python3 -m unittest discover -s tests -v

game:
	python3 language/zeto.py games/murino/game.zeto

fetch:
	python3 apps/zetofetch.py

browse:
	python3 apps/zetobrowse.py $(URL)

zeto-check:
	@mkdir -p $(BUILD)
	python3 language/zeto.py games/murino/game.zeto --emit-python > $(BUILD)/murino.bootstrap.py
	python3 -m py_compile $(BUILD)/murino.bootstrap.py

$(BUILD)/%.o: kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/kernel.elf: $(OBJECTS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

limine:
	@if [ ! -d "$(LIMINE_DIR)" ]; then \
	  git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1 $(LIMINE_DIR); \
	fi
	$(MAKE) -C $(LIMINE_DIR)

iso: all limine
	mkdir -p $(ISO_ROOT)/boot
	cp $(BUILD)/kernel.elf $(ISO_ROOT)/boot/kernel.elf
	cp boot/limine.conf $(ISO_ROOT)/limine.conf
	cp $(LIMINE_DIR)/limine-bios.sys $(ISO_ROOT)/boot/
	cp $(LIMINE_DIR)/limine-bios-cd.bin $(ISO_ROOT)/boot/
	xorriso -as mkisofs -b boot/limine-bios-cd.bin -no-emul-boot \
	  -boot-load-size 4 -boot-info-table $(ISO_ROOT) -o $(BUILD)/zetomir.iso
	$(LIMINE_DIR)/limine bios-install $(BUILD)/zetomir.iso

run: iso
	qemu-system-x86_64 -m 256M -cdrom $(BUILD)/zetomir.iso \
	  -serial stdio -no-reboot -no-shutdown

debug: iso
	qemu-system-x86_64 -m 256M -cdrom $(BUILD)/zetomir.iso \
	  -serial stdio -no-reboot -no-shutdown -s -S

clean:
	rm -rf $(BUILD)
