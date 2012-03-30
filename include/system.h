#ifndef SYSTEM_H
#define SYSTEM_H

void gdt_flush();
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();

void idt_load();
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();

void isrs_install();
//void isr_install_handler(int i, void (*handler)(struct regs* r));
//void isr_uninstall_handler(int i);

struct regs {
	unsigned int gs, fs, es, ds;
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int int_no, err_code;
	unsigned int eip, cs, eflags, useresp, ss;
};

void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs* r));
void irq_uninstall_handler(int irq);

void timer_install();
void timer_phase(int hz);
void timer_wait(int ticks);

void keyboard_install();

#endif
