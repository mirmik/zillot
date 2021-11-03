#ifndef GENOS_DATASTRUCT_UARTRING_H
#define GENOS_DATASTRUCT_UARTRING_H

#include <zillot/cdev.h>
#include <zillot/serial/uart.h>

#include <igris/datastruct/dlist.h>
#include <igris/datastruct/ring.h>
#include <igris/sync/semaphore.h>
#include <igris/sync/waitqueue.h>

typedef struct uartring_s
{
    struct char_device_s dev;
    uart_s *udev;
    sem_t txsem;
    sem_t rxsem;
    waitqueue_t txwait;
    waitqueue_t rxwait;
    char *txbuffer;
    char *rxbuffer;
    struct ring_head txring;
    struct ring_head rxring;
} uartring_s;

__BEGIN_DECLS

void uartring_init(uartring_s *uring, uart_s *uart, void *rxbuf,
                   unsigned int rxsize, void *txbuf, unsigned int txsize);

void uartring_install(struct uartring_s *uring, struct uart_s *uart);

__END_DECLS

extern const struct char_device_operation_s uartring_operations;

#define ZILLOT_DEF_UARTRING(name, uart, txsize, rxsize)                        \
    char name##_rxbuffer[rxsize];                                              \
    char name##_txbuffer[txsize];                                              \
    struct uartring_s name = {                                                 \
        .dev = CHAR_DEVICE_INIT(name, &uartring_operations),                   \
        .udev = uart,                                                          \
        .txsem = SEMAPHORE_INIT(name.txsem, 1),                                \
        .rxsem = SEMAPHORE_INIT(name.rxsem, 1),                                \
        .txwait = WAITQUEUE_INIT(name.txwait),                                 \
        .rxwait = WAITQUEUE_INIT(name.rxwait),                                 \
        .txbuffer = name##_txbuffer,                                           \
        .rxbuffer = name##_rxbuffer,                                           \
        .txring = RING_HEAD_INIT(txsize),                                      \
        .rxring = RING_HEAD_INIT(rxsize)}

#endif