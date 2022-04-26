#ifndef STM32_ASM_SYSTIME_H
#define STM32_ASM_SYSTIME_H

#include <periph/map.h>

typedef int64_t systime_t;
typedef int64_t systime_difference_t;

extern int __systick_config;

#define systime_lomax() __systick_config
#define systime_lopart() (__systick_config - SysTick->VAL)
#define systime_check_flag() (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)

#endif