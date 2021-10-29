#ifndef GENOS_DRIVERS_AVR_UART
#define GENOS_DRIVERS_AVR_UART

#include <zillot/serial/uart.h>
#include <asm/avr_usart.h>
#include <igris/util/macro.h>

#include <avr/interrupt.h>
#include <avr/io.h>

typedef struct avr_usart_device_s
{   
    struct uart_s u;
    struct usart_regs * regs;
} avr_usart_device_s;

extern const struct uart_operations avr_usart_device_ops;

__BEGIN_DECLS

void avr_usart_device_init(avr_usart_device_s* dev);
void avr_usart_device_rx_irq_handler(void * arg);
void avr_usart_device_dre_irq_handler(void * arg);
void avr_usart_device_tx_irq_handler(void * arg);

__END_DECLS

#define __DECLARE_ISR_RX(vect, arg) \
ISR(vect)   { arg.u.handler(arg.u.handarg, UART_IRQCODE_RX); }

#define __DECLARE_ISR_UDRE(vect, arg) \
ISR(vect) { arg.u.handler(arg.u.handarg, UART_IRQCODE_TC); }

#define __DECLARE_ISR_TX(vect, arg) \
ISR(vect)   { arg.u.handler(arg.u.handarg, UART_IRQCODE_TX); }

#define DECLARE_AVR_USART_WITH_IRQS(name, avrlib_name, prefix)   \
avr_usart_device_s name = {UART_INIT(&avr_usart_device_ops,nullptr,nullptr),avrlib_name}; \
__DECLARE_ISR_RX  (prefix##_RX_vect, name)          \
__DECLARE_ISR_UDRE(prefix##_UDRE_vect, name)        \
__DECLARE_ISR_TX  (prefix##_TX_vect, name)              

#endif