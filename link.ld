ENTRY(start)                /* the name of the entry label */
OUTPUT_FORMAT(elf32-i386)
SECTIONS {
    . = 0x00100000;          /* the code should be loaded at 1 MB */

	_kernel_start = .;
    .__mbHeader : {
      *(.__mbHeader)
   }
    /* .multiboot.data : {
        *(.multiboot.data)
    } */

    .__mbText : {
        *(.__mbText)
    }
    . += 0xC0000000;
    /* . += 0x00200000; */
    .text ALIGN (0x1000):   /* align at 4 KB */
    {
        *(.text)
        *(.rodata*)             /* all text sections from all files */
    }

    .data ALIGN (0x1000) :   /* align at 4 KB */
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :    /* align at 4 KB */
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
    _kernel_end = .;
}
