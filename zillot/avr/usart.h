#ifndef ZILLOT_DRIVERS_AVR_UART
#define ZILLOT_DRIVERS_AVR_UART

#include <asm/avr_usart.h>
#include <igris/util/macro.h>
#include <zillot/common/uart.h>

#include <avr/interrupt.h>
#include <avr/io.h>

namespace zillot 
{
    namespace avr 
    {
        class usart : public zillot::uart 
        {
        public:
            usart_regs* regs;
            int irqno;

        public:
            usart(usart_regs * _regs, int irqno) : regs(_regs), irqno(irqno) {}
            int setup(int32_t baud, char parity, uint8_t databits, uint8_t stopbits) override;
            int enable(int en) override;
            int ctrirqs(uint8_t cmd) override;
            int recvbyte() override;
            int sendbyte(int c) override;
            int cantx() override;
            int hasrx() override;
            //void init_gpio(zillot::stm32::pin tx, zillot::stm32::pin rx, int af);
            void irqinit();
        };
    }
}

#define __DECLARE_ISR_RX(vect, arg)                                            \
    ISR(vect) { arg.dev.handler(arg.dev.handarg, UART_IRQCODE_RX); }

// Да так должно быть: ISR_UDRE и IRQCODE_TX
#define __DECLARE_ISR_UDRE(vect, arg)                                          \
    ISR(vect) { arg.dev.handler(arg.dev.handarg, UART_IRQCODE_TX); }

// Да так должно быть: ISR_TX и IRQCODE_TC
#define __DECLARE_ISR_TX(vect, arg)                                            \
    ISR(vect) { arg.dev.handler(arg.dev.handarg, UART_IRQCODE_TC); }

#define DECLARE_AVR_USART_WITH_IRQS(name, avrlib_name, prefix)                 \
    avr_usart_device_s name = {                                                \
        UART_INIT(&avr_usart_device_ops, nullptr, nullptr), avrlib_name};      \
    __DECLARE_ISR_RX(prefix##_RX_vect, name)                                   \
    __DECLARE_ISR_UDRE(prefix##_UDRE_vect, name)                               \
    __DECLARE_ISR_TX(prefix##_TX_vect, name)

#endif