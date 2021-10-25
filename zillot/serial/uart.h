#ifndef ZILLOT_UART_DEVICE_H
#define ZILLOT_UART_DEVICE_H

#include <stdint.h>

#define UART_IRQCODE_RX 0
#define UART_IRQCODE_TX 1 // Можно положить следующий байт
#define UART_IRQCODE_TC 2 // Конвеер завершил свою работу.

#define UART_IRQCODE_ERROR_MASK 0x80
#define UART_IRQCODE_RX_OVERRUN 0x81

#define UART_CTRIRQS_RXON 0
#define UART_CTRIRQS_RXOFF 1
#define UART_CTRIRQS_TXON 2
#define UART_CTRIRQS_TXOFF 3
#define UART_CTRIRQS_TCON 4
#define UART_CTRIRQS_TCOFF 5

struct uart_operations 
{
	int (*setup)(struct uart_s * uart, int32_t baud, char parity, uint8_t databits, uint8_t stopbits);
	int (*enable)(struct uart_s * uart, int en);
	int (*ctrirqs)(struct uart_s * uart, uint8_t cmd);
	int (*recvbyte)(struct uart_s * uart);
	int (*sendbyte)(struct uart_s * uart, int c);
	int (*cantx)(struct uart_s * uart);
	int (*hasrx)(struct uart_s * uart);
};

typedef struct uart_s
{
	const uart_operations * u_ops;
	void (*handler)(void* arg, int code);
	void*  handarg;
} uart_s;


#define UART_INIT(ops,handler,handarg) {ops,handler,handarg} 

#endif
