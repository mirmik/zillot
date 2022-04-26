#ifndef ZILLOT_STM32_USART_H
#define ZILLOT_STM32_USART_H

#include <zillot/common/usart.h>
#include <stm32f4xxxx.h>

namespace zillot 
{
	namespace stm32 
	{
		class usart 
		{
			TypeDef_USART * _regs;
			int irqno;

		public:
			usart(TypeDef_USART * _regs, int irqno);
		};
	}
}

#endif