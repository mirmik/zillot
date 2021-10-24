#ifndef ZILLOT_ARDUINO_PIN_H
#define ZILLOT_ARDUINO_PIN_H

#include <asm/avr_gpio.h>

struct arduino_pin
{
    gpio_regs *regs;
    int mask;

    void set(bool en) { avr_gpio_set(regs, mask, en); }
    int get() { return avr_gpio_get(regs, mask); }
    int mode(uint32_t m) { return avr_gpio_mode(regs, mask, m); }
};

#endif