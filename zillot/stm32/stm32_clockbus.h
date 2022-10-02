#ifndef STM32_CLOCKBUS_H
#define STM32_CLOCKBUS_H

#include <stdint.h>
#include <sys/cdefs.h>

#define CLOCKBUS_HSI 0
#define CLOCKBUS_HSE 1
#define CLOCKBUS_MSI 2
#define CLOCKBUS_PLL 3
#define CLOCKBUS_APB1 4
#define CLOCKBUS_APB2 5

extern uint32_t stm32_clockbus_freq[6];

__BEGIN_DECLS

void stm32_clockbus_enable_hsi_mode();

void stm32_clockbus_simple_hsi_mode();
void stm32_clockbus_hsi_mode();
void stm32_clockbus_hse_mode();
void stm32_clockbus_reevaluate();
void stm32_clockbus_systime_setup();

void stm32_clockbus_set_hpre_divider(int divider);
uint16_t stm32_clockbus_get_hpre_divider();
void stm32_clockbus_set_ppre1_divider(int divider);
uint16_t stm32_clockbus_get_ppre1_divider();
void stm32_clockbus_set_ppre2_divider(int divider);
uint16_t stm32_clockbus_get_ppre2_divider();

__END_DECLS

#endif