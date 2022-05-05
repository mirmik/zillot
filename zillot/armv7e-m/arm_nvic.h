#ifndef ZILLOT_ARMV7E_NVIC_M
#define ZILLOT_ARMV7E_NVIC_M

#include <stm32xxxx.h> /// < Почему это в armv7e-m?
#include <igris/compiler.h>

#define NVIC_IRQNO(x) (x+16)

__BEGIN_DECLS

static inline 
void nvic_enable_irq(uint32_t irqno) 
{
	irqno = NVIC_IRQNO(irqno);
	uint32_t regno = irqno >> 5;
	uint32_t bitno = irqno & 0x1F;
	NVIC->ISER[regno] |= 1 << bitno;
}
	
static inline 
void nvic_set_priority(int irqno, int32_t prio) 
{
	irqno = NVIC_IRQNO(irqno);
	NVIC->IP[irqno] = prio;
}

__END_DECLS

#endif