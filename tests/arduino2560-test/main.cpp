#include <Arduino.h>
#include <asm/avr_arch.h>
#include <asm/avr_gpio.h>
#include <asm/avr_usart.h>
#include <igris/dprint.h>
#include <igris/time/jiffies-systime.h>
#include <igris/util/cpu_delay.h>

int main()
{
    arch_init();

    irqs_enable();
    avr_usart_setup(USART0, 115200, 'n', 8, 1);
    pinMode(13, 1);

    while (1)
    {
        dprln(igris::millis());
        digitalWrite(13, 1);
        delay(500);
        digitalWrite(13, 0);
        delay(500);
    }
}