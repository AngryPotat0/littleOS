for i in range(1,33):
    print("idtInstall({k}, (unsigned long)isr{k},0x08,0x8e);".format(k = i))

#qemu-system-i386 -m 512M -smp 2 -boot c -cpu host  --enable-kvm -cdrom os.iso