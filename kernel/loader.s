extern main
extern kernel_start
extern kernel_end

[global mutiboot_addr32]
[global kernel_start_addr]
[global kernel_end_addr]

global start                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096      ; size of stack in bytes
mb_stack_size equ 4096

section .__mbHeader
align 0x4
	dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum
	; mb_stack:
    ; 	resb mb_stack_size

section .__mbText
align 0x4

start:
	mov [mutiboot_addr32], ebx
	lea ebx, [loader] ; load the address of the label in ebx
    jmp ebx           ; jump to the label



section .bss
align 4                         ; align at 4 bytes
kernel_stack:
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .data
align 4
mutiboot_addr32:
	dd 0x0

kernel_start_addr:
	dd kernel_start

kernel_end_addr:
	dd kernel_end

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned

loader:                         ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the
                                                ; stack (end of memory area)
    call main  

.loop:
    jmp .loop                   ; loop forever


[global getEsp]
getEsp:
	mov eax,esp
	ret

[global switchTo]
switchTo:
	mov [eax+28],esp
	mov eax,[esp+4] ;第一个参数 
	mov [eax],ebp
	mov [eax+4],ebx
	mov [eax+8],ecx
	mov [eax+12],edx
	mov [eax+16],esi
	mov [eax+20],edi
	push ebx
	mov ebx,eax
	pushf
	pop eax
	mov [ebx+24],eax
	mov eax,ebx
	pop ebx

	mov eax,[esp+8] ;第二个参数
	mov esp,[eax+28]
	mov ebp,[eax]
	mov ebx,[eax+4]
	mov ecx,[eax+8]
	mov edx,[eax+12]
	mov esi,[eax+16]
	mov edi,[eax+20]
	add eax,24
	push dword [eax] ;eflags
	popf	

	mov al,0x20         
	out 0xA0,al
	out 0x20,al
	
	ret

[global _mm_pause]
_mm_pause:
	PAUSE

[global gdtFlush];load gdt
[extern gp]

gdtFlush:      
    lgdt [gp]
    jmp 0x8:flush2
flush2:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ax, 0x38;load tss
    ltr ax
    ret

[global idtLoad];load idt
[extern idtp]

idtLoad:
	; call printMSG
    lidt [idtp]
	; sti
    ret

[bits 32]
%macro NO_ERROCODE 1     ;带中断号参数宏
[GLOBAL isr%1]
isr%1:
		cli
		push eax
		mov eax,esp      ;中断参数传入
		push 0
		push %1          ;中断号
		jmp pre_handle
%endmacro

%macro HAVE_ERROCODE 1
[GLOBAL isr%1]
isr%1:
		cli
		push eax
		mov eax,esp
		nop
		push %1
		jmp pre_handle

%endmacro


[EXTERN funcRoute]
pre_handle:
	mov ecx,[esp]
	mov ebx,eax
	push ds
	push es
	push fs
	push gs
	pushad

	push ebx     ;传入void *
	push ecx     ;传入int类型中断号
	call funcRoute

	add esp,8
	popad
	pop gs
	pop fs
	pop es
	pop ds
	add esp,8
	pop eax
	sti
	iret


NO_ERROCODE 0
NO_ERROCODE 1
NO_ERROCODE 2
NO_ERROCODE 3
NO_ERROCODE 4
NO_ERROCODE 5
NO_ERROCODE 6
NO_ERROCODE 7
HAVE_ERROCODE 8
NO_ERROCODE 9
HAVE_ERROCODE 10
HAVE_ERROCODE 11
HAVE_ERROCODE 12 
HAVE_ERROCODE 13 
HAVE_ERROCODE 14
NO_ERROCODE 15
NO_ERROCODE 16
HAVE_ERROCODE 17
NO_ERROCODE 18
NO_ERROCODE 19

NO_ERROCODE 20
NO_ERROCODE 21
NO_ERROCODE 22
NO_ERROCODE 23
NO_ERROCODE 24
NO_ERROCODE 25
NO_ERROCODE 26
NO_ERROCODE 27
NO_ERROCODE 28
NO_ERROCODE 29
NO_ERROCODE 30
NO_ERROCODE 31
NO_ERROCODE 32
NO_ERROCODE 33
NO_ERROCODE 34