#include <zillot/stm32/stm32_gpio.h>
#include <zillot/stm32/stm32_rcc.h>
#include <zillot/stm32/stm32_systick.h>
#include <zillot/stm32/stm32h7_pll.h>
#include <zillot/stm32/pin.h>
#include <zillot/irqtable/irqtable.h>
#include <igris/util/cpu_delay.h>
#include <igris/time/jiffies-systime.h>
#include <igris/time/systime.h>
#include <asm/irq.h>

	zillot::stm32::pin green_led{GPIOB, 1<<6};
	zillot::stm32::pin red_led{GPIOB, 1<<7};

int main() 
{
	irqs_disable();
	irqtable_init();

	// enable clocking from hse
	stm32_enable_hse();
	stm32_system_clock_mux_hse();

	// setup pll
	stm32_disable_pll();
	stm32h7_set_pll1_source_hse();
	stm32h7_set_pll1_coefficients(16, 168, 8);
	
	bits_assign(RCC->D1CFGR, RCC_D1CFGR_D1PPRE_Msk, 
		(0b100)<<RCC_D1CFGR_D1PPRE_Pos);

	bits_assign(RCC->D2CFGR, RCC_D2CFGR_D2PPRE1_Msk, 
		(0b100)<<RCC_D2CFGR_D2PPRE1_Pos);

	bits_assign(RCC->D2CFGR, RCC_D2CFGR_D2PPRE2_Msk, 
		(0b100)<<RCC_D2CFGR_D2PPRE2_Pos);

	bits_assign(RCC->D1CFGR, RCC_D3CFGR_D3PPRE_Msk, 
		(0b100)<<RCC_D3CFGR_D3PPRE_Pos);

	stm32_enable_pll();
	stm32_system_clock_mux_pll(0);

	int systick_freq = 1000;
	int64_t sysfreq = 32000000 / 16 * 168 / 8;
	stm32_systick_config(sysfreq / systick_freq);
	systime_set_frequency(systick_freq);

	irqtable_set_handler(
        SysTick_IRQn, (void (*)(void *))jiffies_increment, NULL);

	stm32_rcc_enable_gpio(GPIOA);
	stm32_rcc_enable_gpio(GPIOB);
	stm32_rcc_enable_gpio(GPIOC);

	green_led.setup(GPIO_MODE_OUTPUT);
	red_led.setup(GPIO_MODE_OUTPUT);
	green_led.set(0);
	red_led.set(0);

	irqs_enable();

	while(1) {
		green_led.set(1);
		red_led.set(0);

		igris::delay(1000);

		green_led.set(0);
		red_led.set(1);

		igris::delay(1000);
	}
}