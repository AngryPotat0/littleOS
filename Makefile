# OBJECTS = loader.o kmain.o port.o screen.o util.o gdt.o interrupt.o asm.o
# CC = i386-elf-gcc
# CFLAGS = -ffreestanding  -nostdlib -nostartfiles
# LDFLAGS = -T link.ld -melf_i386
# AS = nasm
# ASFLAGS = -f elf

# all: kernel.elf

# kernel.elf: $(OBJECTS)
# 	i386-elf-ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

# os.iso: kernel.elf
# 	cp kernel.elf iso/boot/kernel.elf
# 	genisoimage -R                              \
# 				-b boot/grub/stage2_eltorito    \
# 				-no-emul-boot                   \
# 				-boot-load-size 4               \
# 				-A os                           \
# 				-input-charset utf8             \
# 				-quiet                          \
# 				-boot-info-table                \
# 				-o os.iso                       \
# 				iso

# run: os.iso
# 	 bochs -f bch.txt -q

# %.o: %.c
# 	$(CC) $(CFLAGS)  $< -o $@

# %.o: %.s
# 	$(AS) $(ASFLAGS) $< -o $@

# clean:
# 	rm -rf *.o kernel.elf


C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard include/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 

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


%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c -std=c11 -nostdlib -nostartfiles $< -o $@

%.o: %.s
	nasm $< -f elf -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
