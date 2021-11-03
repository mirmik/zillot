#ifndef ZILLOT_UART_DEVICE_H
#define ZILLOT_UART_DEVICE_H

#include <igris/compiler.h>
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

struct uart_s;
struct uart_operations
{
    int (*setup)(struct uart_s *uart, int32_t baud, char parity,
                 uint8_t databits, uint8_t stopbits);
    int (*enable)(struct uart_s *uart, int en);
    int (*ctrirqs)(struct uart_s *uart, uint8_t cmd);
    int (*recvbyte)(struct uart_s *uart);
    int (*sendbyte)(struct uart_s *uart, int c);
    int (*cantx)(struct uart_s *uart);
    int (*hasrx)(struct uart_s *uart);
};

typedef struct uart_s
{
    const struct uart_operations *u_ops;
    void (*handler)(void *arg, int code);
    void *handarg;
} uart_s;

__BEGIN_DECLS

static inline int uart_cantx(struct uart_s *uart)
{
    return uart->u_ops->cantx(uart);
}
static inline int uart_hasrx(struct uart_s *uart)
{
    return uart->u_ops->hasrx(uart);
}
static inline int uart_setup(struct uart_s *uart, int32_t baud, char parity,
                             uint8_t databits, uint8_t stopbits)
{
    return uart->u_ops->setup(uart, baud, parity, databits, stopbits);
}
static inline int uart_enable(struct uart_s *uart, int en)
{
    return uart->u_ops->enable(uart, en);
}
static inline int uart_ctrirqs(struct uart_s *uart, uint8_t cmd)
{
    return uart->u_ops->ctrirqs(uart, cmd);
}
static inline int uart_recvbyte(struct uart_s *uart)
{
    return uart->u_ops->recvbyte(uart);
}
static inline int uart_sendbyte(struct uart_s *uart, char c)
{
    return uart->u_ops->sendbyte(uart, c);
}

__END_DECLS

#define UART_INIT(ops, handler, handarg)                                       \
    {                                                                          \
        ops, handler, handarg                                                  \
    }

#endif
