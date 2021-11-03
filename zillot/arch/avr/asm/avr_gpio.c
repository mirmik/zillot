#include <asm/avr_gpio.h>
#include <igris/util/bug.h>
#include <zillot/gpiodefs.h>

int avr_gpio_set(struct gpio_regs *g, uint16_t mask, unsigned char level)
{
    if (level)
        g->port |= mask;
    else
        g->port &= ~mask;

    return 0;
}

int avr_gpio_get(struct gpio_regs *g, uint16_t mask) { return g->pin; }

int avr_gpio_toggle(struct gpio_regs *g, uint16_t mask)
{
    g->pin = mask;

    return 0;
}

int avr_gpio_mode(struct gpio_regs *g, uint16_t mask, int32_t mode)
{
    if ((mode & GPIO_MODE_OUT_SECTION) &&
        (mode & GPIO_MODE_IN_SECTION)) /* mode is incorrect */
    {
        return -1;
    }

    if (mode & GPIO_MODE_INPUT)
    {
        g->ddr &= ~mask;

        if (mode & GPIO_MODE_IN_NOPULL)
        {
            return -1;
        }

        if (mode & GPIO_MODE_IN_PULL_UP)
        {
            return -1;
        }

        if (mode & GPIO_MODE_IN_PULL_DOWN)
        {
            return -1;
        }

        if (mode & GPIO_MODE_IN_SCHMITT)
        {
            return -1;
        }

        return 0;
    };

    if (mode & GPIO_MODE_OUTPUT)
    {
        g->ddr |= mask;
        return 0;
    };
}