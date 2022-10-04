#include <igris/util/bits.h>
#include <stm32xxxx.h>
#include <zillot/stm32/stm32_clockbus.h>
#include <zillot/stm32/stm32_systick.h>

// static int __active_mode = 0;
// static int __systembus = 0;

void stm32_clockbus_enable_hsi_mode()
{
    volatile int i;
    RCC->CR = RCC_CR_HSION;
    i = 1000;
    while (--i)
        ;
}

uint32_t hpre_divider_value(uint16_t divider)
{
    switch (divider)
    {
    case 1:
        return RCC_CFGR_HPRE_DIV1;
    case 2:
        return RCC_CFGR_HPRE_DIV2;
    case 4:
        return RCC_CFGR_HPRE_DIV4;
    case 8:
        return RCC_CFGR_HPRE_DIV8;
    case 16:
        return RCC_CFGR_HPRE_DIV16;
    case 64:
        return RCC_CFGR_HPRE_DIV64;
    case 128:
        return RCC_CFGR_HPRE_DIV128;
    case 256:
        return RCC_CFGR_HPRE_DIV256;
    case 512:
        return RCC_CFGR_HPRE_DIV512;
    }
    return 0;
}

uint32_t ppre1_divider_value(uint16_t divider)
{
    switch (divider)
    {
    case 1:
        return RCC_CFGR_PPRE1_DIV1;
    case 2:
        return RCC_CFGR_PPRE1_DIV2;
    case 4:
        return RCC_CFGR_PPRE1_DIV4;
    case 8:
        return RCC_CFGR_PPRE1_DIV8;
    case 16:
        return RCC_CFGR_PPRE1_DIV16;
    }
    return 0;
}

uint32_t ppre2_divider_value(uint16_t divider)
{
    switch (divider)
    {
    case 1:
        return RCC_CFGR_PPRE2_DIV1;
    case 2:
        return RCC_CFGR_PPRE2_DIV2;
    case 4:
        return RCC_CFGR_PPRE2_DIV4;
    case 8:
        return RCC_CFGR_PPRE2_DIV8;
    case 16:
        return RCC_CFGR_PPRE2_DIV16;
    }
    return 0;
}

uint16_t hpre_value_to_divider(uint32_t value)
{
    switch (value)
    {
    case RCC_CFGR_HPRE_DIV1:
        return 1;
    case RCC_CFGR_HPRE_DIV2:
        return 2;
    case RCC_CFGR_HPRE_DIV4:
        return 4;
    case RCC_CFGR_HPRE_DIV8:
        return 8;
    case RCC_CFGR_HPRE_DIV16:
        return 16;
    case RCC_CFGR_HPRE_DIV64:
        return 64;
    case RCC_CFGR_HPRE_DIV128:
        return 128;
    case RCC_CFGR_HPRE_DIV256:
        return 256;
    case RCC_CFGR_HPRE_DIV512:
        return 512;
    }
    return 0;
}

uint16_t ppre1_value_to_divider(uint32_t value)
{
    switch (value)
    {
    case RCC_CFGR_PPRE1_DIV1:
        return 1;
    case RCC_CFGR_PPRE1_DIV2:
        return 2;
    case RCC_CFGR_PPRE1_DIV4:
        return 4;
    case RCC_CFGR_PPRE1_DIV8:
        return 8;
    case RCC_CFGR_PPRE1_DIV16:
        return 16;
    }
    return 0;
}

uint16_t ppre2_value_to_divider(uint32_t value)
{
    switch (value)
    {
    case RCC_CFGR_PPRE2_DIV1:
        return 1;
    case RCC_CFGR_PPRE2_DIV2:
        return 2;
    case RCC_CFGR_PPRE2_DIV4:
        return 4;
    case RCC_CFGR_PPRE2_DIV8:
        return 8;
    case RCC_CFGR_PPRE2_DIV16:
        return 16;
    }
    return 0;
}

void stm32_clockbus_set_hpre_divider(int divider)
{
    uint32_t value = hpre_divider_value(divider);
    bits_assign(RCC->CFGR, RCC_CFGR_HPRE, value);
}

uint16_t stm32_clockbus_get_hpre_divider()
{
    uint32_t value = bits_mask(RCC->CFGR, RCC_CFGR_HPRE);
    return hpre_value_to_divider(value);
}

void stm32_clockbus_set_ppre1_divider(int divider)
{
    uint32_t value = ppre1_divider_value(divider);
    bits_assign(RCC->CFGR, RCC_CFGR_PPRE1, value);
}

uint16_t stm32_clockbus_get_ppre1_divider()
{
    uint32_t value = bits_mask(RCC->CFGR, RCC_CFGR_PPRE1);
    return ppre1_value_to_divider(value);
}

void stm32_clockbus_set_ppre2_divider(int divider)
{
    uint32_t value = ppre2_divider_value(divider);
    bits_assign(RCC->CFGR, RCC_CFGR_PPRE2, value);
}

uint16_t stm32_clockbus_get_ppre2_divider()
{
    uint32_t value = bits_mask(RCC->CFGR, RCC_CFGR_PPRE2);
    return ppre2_value_to_divider(value);
}

/*
void stm32_clockbus_hse_mode()
{
    volatile int i;
    RCC->CR |= RCC_CR_CSSON;
    i = 1000; while (--i);

#ifdef RCC_APB1ENR1_PWREN
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;              // Power interface clock
enable #else RCC->APB1ENR |= RCC_APB1ENR_PWREN; #endif

    i = 1000; while (--i);

#ifdef RCC_APB1ENR1_PWREN
    while ((RCC->APB1ENR1 & RCC_APB1ENR1_PWREN) != RCC_APB1ENR1_PWREN) {};
#else
    while ((RCC->APB1ENR & RCC_APB1ENR_PWREN) != RCC_APB1ENR_PWREN) {};
#endif

    RCC->CFGR &= ~(RCC_CFGR_HPRE_DIV16 | RCC_CFGR_PPRE1_DIV16 |
RCC_CFGR_PPRE2_DIV16); RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV1 |
RCC_CFGR_PPRE2_DIV1; stm32_clockbus_set_dividers(1, 1);

    // Запуск HSE и ожидание включения
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |= (RCC_CFGR_SW_HSE);
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);

    //RCC->CR &= ~RCC_CR_HSION;
    //i = 1000; while (--i);

    __active_mode = 1;
    __systembus = CLOCKBUS_HSE;
    stm32_clockbus_reevaluate();
}

void stm32_clockbus_reevaluate()
{
    switch (__active_mode)
    {
        case 0:
            stm32_clockbus_freq[CLOCKBUS_APB1] =
stm32_clockbus_freq[CLOCKBUS_HSI] / __dividers[0];
            stm32_clockbus_freq[CLOCKBUS_APB2] =
stm32_clockbus_freq[CLOCKBUS_HSI] / __dividers[1]; break; case 1:
            stm32_clockbus_freq[CLOCKBUS_APB1] =
stm32_clockbus_freq[CLOCKBUS_HSE] / __dividers[0];
            stm32_clockbus_freq[CLOCKBUS_APB2] =
stm32_clockbus_freq[CLOCKBUS_HSE] / __dividers[1]; break; case 2:
            stm32_clockbus_freq[CLOCKBUS_APB1] =
stm32_clockbus_freq[CLOCKBUS_PLL] / __dividers[0];
            stm32_clockbus_freq[CLOCKBUS_APB2] =
stm32_clockbus_freq[CLOCKBUS_PLL] / __dividers[1]; break;
    }
}*/

/*void stm32_clockbus_systime_setup()
{
    stm32_systick_config(stm32_clockbus_freq[__systembus] / 1000);
    //sysclock_set_frequency(stm32_clockbus_freq[__systembus]);
    //init_delays(stm32_clockbus_freq[__systembus]);
    //systime_set_frequency(1000);
}

int stm32_clockbus_enable_pll_mode(uint32_t freq)
{
    __active_mode = 2;
    __systembus = CLOCKBUS_PLL;
    stm32_clockbus_freq[__systembus] = freq;
    stm32_clockbus_reevaluate();
    stm32_clockbus_systime_setup();

    return 0;
}*/