#ifndef AVR2560_USART_H
#define AVR2560_USART_H

#include <avr/io.h>
#include <igris/compiler.h>
#include <igris/util/bits.h>

struct usart_regs
{
    volatile uint8_t ucsr_a;
    volatile uint8_t ucsr_b;
    volatile uint8_t ucsr_c;
    volatile uint8_t reserve0;
    volatile uint8_t ubrr_l;
    volatile uint8_t ubrr_h;
    volatile uint8_t udr;
} __attribute__((packed));

__BEGIN_DECLS

int avr_usart_sendbyte(struct usart_regs *regs, char c);
int avr_usart_recvbyte(struct usart_regs *regs);
int avr_usart_cansend(struct usart_regs *regs);
int avr_usart_canrecv(struct usart_regs *regs);
void avr_usart_enable_rx(struct usart_regs *regs, int en);
void avr_usart_enable_tx(struct usart_regs *regs, int en);
void avr_usart_rxirq(struct usart_regs *regs, int en);
void avr_usart_txirq(struct usart_regs *regs, int en);
void avr_usart_tcirq(struct usart_regs *regs, int en);
void avr_usart_setup(struct usart_regs *regs, uint32_t baud, char parity,
                     uint8_t databits, uint8_t stopbits);

__END_DECLS

#define USART0 ((struct usart_regs *)(&UCSR0A))

#endif