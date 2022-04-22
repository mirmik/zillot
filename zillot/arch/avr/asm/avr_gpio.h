#ifndef AVR_GPIO_H
#define AVR_GPIO_H

#include <stdint.h>
#include <igris/compiler.h>

#include <avr/io.h>

struct gpio_regs
{
    volatile uint8_t pin;
    volatile uint8_t ddr;
    volatile uint8_t port;
} __attribute__((packed));

__BEGIN_DECLS

int avr_gpio_set(struct gpio_regs *g, uint16_t mask, unsigned char level);
int avr_gpio_get(struct gpio_regs *g, uint16_t mask);
int avr_gpio_toggle(struct gpio_regs *g, uint16_t mask);
int avr_gpio_mode(struct gpio_regs *g, uint16_t mask, int32_t mode);

__END_DECLS

#define GPIOA ((struct gpio_regs *)(&PINA))
#define GPIOB ((struct gpio_regs *)(&PINB))
#define GPIOC ((struct gpio_regs *)(&PINC))
#define GPIOD ((struct gpio_regs *)(&PIND))
#define GPIOE ((struct gpio_regs *)(&PINE))
#define GPIOF ((struct gpio_regs *)(&PINF))
#define GPIOH ((struct gpio_regs *)(&PINH))
#define GPIOL ((struct gpio_regs *)(&PINL))
#define GPIOG ((struct gpio_regs *)(&PING))
#define GPIOJ ((struct gpio_regs *)(&PINJ))
#define GPIOK ((struct gpio_regs *)(&PINK))

#endif