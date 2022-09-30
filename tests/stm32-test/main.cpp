#include <igris/util/cpu_delay.h>
#include <stm32xxxx.h>
#include <zillot/stm32/pin.h>
#include <zillot/stm32/stm32_rcc.h>
#include <zillot/stm32/usart.h>

// stm32f401re led
zillot::stm32::pin board_led(GPIOA, 1 << 5);
zillot::stm32::usart board_usart(USART2, USART2_IRQn);

int main()
{
    stm32_rcc_enable_gpio(GPIOA);
    board_led.setup(GPIO_MODE_OUTPUT);
    board_usart.setup(115200, 'n', 8, 1);

    while (1)
    {
        board_usart.sendbyte('a');
        board_led.toggle();
        cpu_delay(100000);
    }
}
