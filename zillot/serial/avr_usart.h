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

/*public:
    int setup(int32_t baud, char parity, uint8_t databits, uint8_t stopbits) override;
    int enable(int en) override;
    int ctrirqs(uint8_t cmd) override;
    int recvbyte() override;
    int sendbyte(int c) override;
    int cantx() override;
    int hasrx() override;

    avr_usart_device(struct usart_regs * regs) 
        : regs(regs) 
    {}

#if defined DRIVERS_WITH_IRQTABLE 
    int irqinit(int base_irqno);
#endif*/
} avr_usart_device_s;

__BEGIN_DECLS

void avr_usart_device_init(avr_usart_device_s* dev);
void avr_usart_device_rx_irq_handler(void * arg);
void avr_usart_device_dre_irq_handler(void * arg);
void avr_usart_device_tx_irq_handler(void * arg);

__END_DECLS

#define __DECLARE_ISR_RX(vect, arg) \
ISR(vect)   { arg.handler(arg.handarg, UART_IRQCODE_RX); }

#define __DECLARE_ISR_UDRE(vect, arg) \
ISR(vect) { arg.handler(arg.handarg, UART_IRQCODE_TC); }

#define __DECLARE_ISR_TX(vect, arg) \
ISR(vect)   { arg.handler(arg.handarg, UART_IRQCODE_TX); }

#define DECLARE_AVR_USART_WITH_IRQS(usart, device_name) \
avr_usart_device usart(device_name);                    \
__DECLARE_ISR_RX  (device_name##_RX_vect, usart)        \
__DECLARE_ISR_UDRE(device_name##_UDRE_vect, usart)      \
__DECLARE_ISR_TX  (device_name##_TX_vect, usart)              

#endif