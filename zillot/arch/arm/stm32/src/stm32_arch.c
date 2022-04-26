//#include <hal/arch.h>

/*#include <periph/map.h>
#include <periph/irqdefs.h>
#include <periph/coremap.h>

#include <asm/stm32_rcc.h>
#include <asm/stm32_systick.h>

#include <asm/irq.h>
#include <igris/time/systime.h>

#ifdef HAS_ZILLOT_IQR_TABLE
#include <hal/irqtable.h>
#endif

#if defined(STM32F4XX) || defined(STM32G4XX) || defined(STM32L4XX) || defined(STM32F7XX)
#define HSI_FREQ 16000000
#else
#error "undefined HSI frequency"
#endif

void stm32_sysinit();

static void init_systick_hsi() 
{
	stm32_systick_config(HSI_FREQ / 1000);
	sysclock_set_frequency(HSI_FREQ);
	init_delays(HSI_FREQ);
	systime_set_frequency(1000);

#ifdef HAS_ZILLOT_IQR_TABLE
	irqtable_set_handler(SysTick_IRQn, system_tick, NULL);
#endif
}

void arch_init() 
{
	irqs_disable();

	stm32_clockbus_freq[CLOCKBUS_HSI] = HSI_FREQ;
	stm32_sysinit(); // Инициализация конкретной архитектуры

	irqtable_init();
	init_systick_hsi();
}*/