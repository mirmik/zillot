#ifndef ZILLOT_STM32_USART_H
#define ZILLOT_STM32_USART_H

#include <zillot/common/uart.h>
#include <zillot/stm32/pin.h>
#include <stm32xxxx.h>

namespace zillot 
{
	namespace stm32 
	{
		class usart : public zillot::uart 
		{
		public:
			USART_TypeDef* regs;
			int irqno;

		public:
			usart(USART_TypeDef * _regs, int irqno) : regs(_regs), irqno(irqno) {}
			int setup(int32_t baud, char parity, uint8_t databits, uint8_t stopbits) override;
			int enable(int en) override;
			int ctrirqs(uint8_t cmd) override;
			int recvbyte() override;
			int sendbyte(int c) override;
			int cantx() override;
			int hasrx() override;

			void init_gpio(zillot::stm32::pin tx, zillot::stm32::pin rx, int af);
			void irqinit();

			void irq_handler();
		};
	}
}

#endif