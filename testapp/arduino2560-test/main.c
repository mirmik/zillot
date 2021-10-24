#include <Arduino.h>
#include <asm/avr_gpio.h>
#include <igris/time/systime.h>
#include <igris/util/cpu_delay.h>

int main()
{
    pinMode(13, 1);

    while (1)
    {
        cpu_delay(100000);
        digitalWrite(13, 1);
        cpu_delay(100000);
        digitalWrite(13, 0);
    }
}