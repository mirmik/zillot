#include <asm/avr_diag.h>
#include <asm/avr_timer.h>

#include <igris/time/jiffies-systime.h>

void arch_init()
{
    avr_timer8_ovfirq_enable(TIMER0, 1);
    avr_timer8_divider(TIMER0, 64);

    systime_set_frequency(F_CPU / 256 / 64);

    usart0_diag_init();
}
