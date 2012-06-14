;
; boot.s -- Kernel start location. Also defines multiboot header.
;           Based on Bran's kernel development tutorial file start.asm
;

MBOOT_PAGE_ALIGN    equ 1<<0    ; Load kernel and modules on a page boundary
MBOOT_MEM_INFO      equ 1<<1    ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
; NOTE: We do not use MBOOT_AOUT_KLUDGE. It means that GRUB does not
; pass us a symbol table.
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


[BITS 32]                       ; All instructions should be 32-bit.

[GLOBAL mboot]                  ; Make 'mboot' accessible from C.
[EXTERN code]                   ; Start of the '.text' section.
[EXTERN bss]                    ; Start of the .bss section.
[EXTERN end]                    ; End of the last loadable section.

mboot:
    dd  MBOOT_HEADER_MAGIC      ; GRUB will search for this value on each
                                ; 4-byte boundary in your kernel file
    dd  MBOOT_HEADER_FLAGS      ; How GRUB should load your file / settings
    dd  MBOOT_CHECKSUM          ; To ensure that the above values are correct

    dd  mboot                   ; Location of this descriptor
    dd  code                    ; Start of kernel '.text' (code) section.
    dd  bss                     ; End of kernel '.data' section.
    dd  end                     ; End of kernel.
    dd  start                   ; Kernel entry point (initial EIP).

[GLOBAL start]                  ; Kernel entry point.
[EXTERN main]                   ; This is the entry point of our C code

start:
	push esp
    ; Load multiboot information:
    push    ebx

    ; Execute the kernel:
    cli                         ; Disable interrupts.	
	call main                   ; call our main() function.
    jmp $                       ; Enter an infinite loop, to stop the processor
                                ; executing whatever rubbish is in the memory
                                ; after our kernel!

global gdt_flush
extern gp
gdt_flush:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2 ; 0x08 is the offset to our code segment: Far jump!
flush2:
	ret

global idt_load
extern idtp
idt_load:
	lidt [idtp]
	ret

; Oh the joyous ISRS!
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
isr0: ; Divide by zero exception
	cli
	push byte 0	; pushed to maintain uniform stack frame
	push byte 0
	jmp isr_common_stub
isr1: ; Debug exception
	cli
	push byte 0
	push byte 1
	jmp isr_common_stub
isr2: ; Non Maskable Interrupt Exception
	cli
	push byte 0
	push byte 2
	jmp isr_common_stub
isr3: ; Breakpoint Exception
	cli
	push byte 0
	push byte 3
	jmp isr_common_stub
isr4: ; Into Detected Overflow Exception
	cli
	push byte 0
	push byte 4	
	jmp isr_common_stub
isr5: ; Out of Bounds Exception
	cli
	push byte 0
	push byte 5
	jmp isr_common_stub
isr6: ; Invalid Opcode Exception
	cli
	push byte 0
	push byte 6
	jmp isr_common_stub
isr7: ; No Coprocessor Exception
	cli
	push byte 0
	push byte 7
	jmp isr_common_stub
isr8: ; Double Fault Exception (ERROR CODE)
	cli
	push byte 8 ; we don't push anything extra onto the stack
				; because 8 already pushes an error code
	jmp isr_common_stub
isr9: ; Coprocessor Segment Overrun Exception
	cli
	push byte 0
	push byte 9
	jmp isr_common_stub
isr10: ; Bad TSS Exception (ERROR CODE)
	cli
	push byte 10
	jmp isr_common_stub
isr11: ; Segment Not Present Exception (ERROR CODE)
	cli
	push byte 11
	jmp isr_common_stub
isr12: ; Stack Fault Exception (ERROR CODE)
	cli
	push byte 12
	jmp isr_common_stub
isr13: ; General Protection Fault Exception (ERROR CODE)
	cli
	push byte 13
	jmp isr_common_stub
isr14: ; Page Fault Exception (ERROR CODE)
	cli
	push byte 14
	jmp isr_common_stub
isr15: ; Unknown Interrupt Exception
	cli
	push byte 0
	push byte 15
	jmp isr_common_stub
isr16: ; Coprocessor Fault Exception
	cli
	push byte 0
	push byte 16
	jmp isr_common_stub
isr17: ; Alignment Check Exception (486+)
	cli
	push byte 0
	push byte 17
	jmp isr_common_stub
isr18: ; Machine Check Exception (Pentium/586+)
	cli
	push byte 0
	push byte 18
	jmp isr_common_stub
isr19: ; Reserved
	cli
	push byte 0
	push byte 19
	jmp isr_common_stub
isr20; ; Reserved
	cli
	push byte 0
	push byte 20
	jmp isr_common_stub
isr21: ; Reserved
	cli
	push byte 0
	push byte 21
	jmp isr_common_stub
isr22: ; Reserved
	cli
	push byte 0
	push byte 22
	jmp isr_common_stub
isr23: ; Reserved
	cli
	push byte 0
	push byte 23
	jmp isr_common_stub
isr24: ; Reserved
	cli
	push byte 0
	push byte 24
	jmp isr_common_stub
isr25: ; Reserved
	cli
	push byte 0
	push byte 25
	jmp isr_common_stub
isr26: ; Reserved
	cli
	push byte 0
	push byte 26
	jmp isr_common_stub
isr27: ; Reserved
	cli
	push byte 0
	push byte 27
	jmp isr_common_stub
isr28: ; Reserved
	cli
	push byte 0
	push byte 28
	jmp isr_common_stub
isr29: ; Reserved
	cli	
	push byte 0
	push byte 29
	jmp isr_common_stub
isr30: ; Reserved
	cli
	push byte 0
	push byte 30
	jmp isr_common_stub
isr31: ; Reserved
	cli
	push byte 0
	push byte 31
	jmp isr_common_stub

extern fault_handler
isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10 	; Load the Kernel Data Segment Descriptor!
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp 	; Push us the stack
	push eax
	mov eax, fault_handler
	call eax 		; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8		; Cleans up the pushed error code and pushed ISR number
	iret			; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0: ; remapped to 32
	cli
	push byte 0
	push byte 32
	jmp irq_common_stub
irq1:
	cli
	push byte 0
	push byte 33
	jmp irq_common_stub
irq2:
	cli
	push byte 0
	push byte 34
	jmp irq_common_stub
irq3:
	cli
	push byte 0
	push byte 35
	jmp irq_common_stub
irq4:
	cli
	push byte 0
	push byte 36
	jmp irq_common_stub
irq5:
	cli
	push byte 0
	push byte 37
	jmp irq_common_stub
irq6:
	cli
	push byte 0
	push byte 38
	jmp irq_common_stub
irq7:
	cli
	push byte 0
	push byte 39
	jmp irq_common_stub
irq8:
	cli
	push byte 0
	push byte 40
	jmp irq_common_stub
irq9:
	cli
	push byte 0
	push byte 41
	jmp irq_common_stub
irq10:
	cli
	push byte 0
	push byte 42 		; The Answer!!
	jmp irq_common_stub
irq11:
	cli
	push byte 0
	push byte 43
	jmp irq_common_stub
irq12:
	cli
	push byte 0
	push byte 44
	jmp irq_common_stub
irq13:
	cli
	push byte 0
	push byte 45
	jmp irq_common_stub
irq14:
	cli
	push byte 0
	push byte 46
	jmp irq_common_stub
irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_common_stub


extern irq_handler
; stub created for IRQ based ISRs, calls 'irq_handler' in our C
irq_common_stub
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, irq_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret
	
