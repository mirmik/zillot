#ifndef ZILLOT_ARMV7E_M
#define ZILLOT_ARMV7E_M

namespace zillot 
{
	namespace armv7e_m {
	class nvic 
	{
		static void enable_irq(uint32_t irqno) 
		{
			irqno = NVIC_IRQNO(irqno);
			uint32_t regno = irqno >> 5;
			uint32_t bitno = irqno & 0x1F;
			NVIC->ISER[regno] |= 1 << bitno;
		}
	
		static void set_priority(int irqno, int32_t prio) 
		{
			irqno = NVIC_IRQNO(irqno);
			NVIC->IP[irqno] = prio;
		}
	};
	}
}

#endif