#include <system.h>

int timer_ticks = 0;

/*
	Handles the tiemr. In this case, it's very simple: We
	increment the 'timer_ticks' variable every time the
	timer fires. By default, the timer fires 18.222 times
	per second. Why 18.222Hz? Some engineer at IBM must've
	been smoking something funky
*/
void timer_handler(struct regs* r) {
	timer_ticks++;

	if(timer_ticks % 18 == 0) {
		//approximately a second has passed
		puts("One second has passed\n");
	}
}

void timer_phase(int hz) {
	int divisor = 1193180/hz;
	outb(0x43, 0x36);			//set our command byte 0x36
	outb(0x40, divisor & 0xFF); //low byte of divisor
	outb(0x40, divisor >> 8);   //high byte of divisor
}

void timer_install() {
	irq_install_handler(0, timer_handler);
}

void timer_wait(int ticks) {
	unsigned long eticks;
	
	eticks = timer_ticks + ticks;
	while(timer_ticks < eticks);
}
