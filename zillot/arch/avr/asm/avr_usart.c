#include <asm/avr_usart.h>


int avr_usart_sendbyte(struct usart_regs* regs, char c)
{
	regs->udr = c;
	return 1;
}

int avr_usart_recvbyte(struct usart_regs* regs)
{
	return regs->udr;
}

int avr_usart_cansend(struct usart_regs* regs)
{
	return bits_mask(regs->ucsr_a, (1 << RXC0));
}

int avr_usart_canrecv(struct usart_regs* regs)
{
	return bits_mask(regs->ucsr_a, (1 << UDRE0));
}

void avr_usart_enable_rx(struct usart_regs* regs, int en)
{
	bits_lvl(regs->ucsr_b, (1 << RXEN0), en);
}

void avr_usart_enable_tx(struct usart_regs* regs, int en)
{
	bits_lvl(regs->ucsr_b, (1 << TXEN0), en);
}

void avr_usart_rxirq(struct usart_regs* regs, int en)
{
	bits_lvl(regs->ucsr_b, (1 << RXCIE0), en);
}

void avr_usart_txirq(struct usart_regs* regs, int en)
{
	bits_lvl(regs->ucsr_b, (1 << UDRIE0), en);
}

void avr_usart_tcirq(struct usart_regs* regs, int en)
{
	bits_lvl(regs->ucsr_b, (1 << TXCIE0), en);
}

void avr_usart_setup(
    struct usart_regs* regs,
    uint32_t baud,
    char parity,
    uint8_t databits,
    uint8_t stopbits
)
{
	regs->ucsr_a |= 1 << U2X0;
	uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;

	regs->ubrr_h = baud_setting >> 8;
	regs->ubrr_l = baud_setting;

// PARITY
//	bits_mask_assign_bias(regs->ucsr_c, mode, 0b11, 4);

// STOP BITS
//	bits_mask_assign_bias(regs->ucsr_c, mode, 0b1, 3);

// DATA BITS
//	bits_mask_assign_bias(regs->ucsr_c, mode, 0b011, 1);
//	bits_mask_assign(regs->ucsr_b, mode, 0b100);
}
