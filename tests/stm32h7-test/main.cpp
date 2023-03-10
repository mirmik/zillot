#include <zillot/stm32/stm32_gpio.h>
#include <zillot/stm32/stm32_rcc.h>
#include <zillot/stm32/pin.h>
#include <igris/util/cpu_delay.h>

int main() 
{
	stm32_rcc_enable_gpio(GPIOA);
	stm32_rcc_enable_gpio(GPIOB);
	stm32_rcc_enable_gpio(GPIOC);

	zillot::stm32::pin green_led(GPIOB, 1<<6);
	zillot::stm32::pin red_led(GPIOB, 1<<7);

	green_led.setup(GPIO_MODE_OUTPUT);
	red_led.setup(GPIO_MODE_OUTPUT);
		
	while(1) {
		green_led.set(1);
		red_led.set(0);

		cpu_delay(1000000);

		green_led.set(0);
		red_led.set(1);

		cpu_delay(1000000);
	}
}