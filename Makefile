C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c user/*.c)
HEADERS = $(wildcard include/*.h)
CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

OBJ = ${C_SOURCES:.c=.o  cpu/interrupt.o}

LDFLAGS = -T link.ld -melf_i386


CC = i386-elf-gcc


os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o os.iso                       \
				iso

kernel.elf: kernel/loader.o ${OBJ}
	i386-elf-ld $(LDFLAGS) $^ -o kernel.elf

run: os.iso
	bochs -f bch.txt -q
# qemu-system-i386 -m 512M -smp 2 -boot c -cpu host  --enable-kvm -cdrom os.iso


%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c -std=c11 $< -o $@

%.o: %.s
	nasm $< -f elf -o $@

clean:
	rm -rf *.elf
	rm -rf kernel/*.o iso/boot/*.elf drivers/*.o cpu/*.o libc/*.o user/*.o
