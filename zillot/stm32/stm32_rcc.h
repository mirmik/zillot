#ifndef ASM_STM32_RCC_H
#define ASM_STM32_RCC_H

#include <sys/cdefs.h>
#include <zillot/stm32/stm32_clockbus.h>
#include <stm32xxxx.h>

__BEGIN_DECLS

void stm32_rcc_enable_gpio(GPIO_TypeDef * gpio);
void stm32_rcc_enable_usart(USART_TypeDef * usart);
void stm32_rcc_enable_spi(SPI_TypeDef * spi);
void stm32_rcc_enable_i2c(I2C_TypeDef * spi);
void stm32_rcc_enable_adc(ADC_TypeDef * spi);
void stm32_rcc_enable_timer(TIM_TypeDef * spi);
void stm32_rcc_enable_syscfg();

__END_DECLS

#endif