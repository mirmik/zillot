#ifndef ZILLOT_STM32_USART_H
#define ZILLOT_STM32_USART_H

#include <zillot/common/usart.h>
#include <stm32xxxx.h>

namespace zillot 
{
	namespace stm32 
	{
		class usart 
		{
			USART_TypeDef* _regs;
			int irqno;

		public:
			usart(USART_TypeDef * _regs, int irqno);
		};
	}
}

#endif