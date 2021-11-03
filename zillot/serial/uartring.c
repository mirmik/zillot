#include <zillot/ioflags.h>
#include <zillot/serial/uartring.h>

#include <igris/defs/schedee.h>
#include <igris/dprint.h>
#include <igris/sync/syslock.h>
#include <igris/util/bug.h>

static int uartring_write(struct char_device_s *dev, const void *data,
                          unsigned int size, uint8_t flags)
{
    struct uartring_s *uring = mcast_out(dev, struct uartring_s, dev);
    int curwrited;
    unsigned int writed = 0;

    if (size == 0)
    {
        return 0;
    }

    if (sem_wait(&uring->txsem))
        goto __exit1__;
    system_lock();

    if (uart_cantx(uring->udev) && ring_empty(&uring->txring))
    {
        writed++;
        uart_sendbyte(uring->udev, (*(char *)data));
    }

    while (size != writed)
    {
        curwrited = ring_write(&uring->txring, uring->txbuffer,
                               (char *)data + writed, size - writed);

        if (curwrited)
            uart_ctrirqs(uring->udev, UART_CTRIRQS_TXON);

        writed += curwrited;

        if (writed == size)
            break;

        if (flags & IO_NOBLOCK)
        {
            break;
        }

        // система разлочится при displace и снова залочится при возвращении в
        // поток.
        if (waitqueue_wait(&uring->txwait))
            goto __exit0__;
    }

__exit0__:
    system_unlock();
    sem_post(&uring->txsem);

__exit1__:
    return writed;
}

static int uartring_read(struct char_device_s *dev, void *data,
                         unsigned int size, uint8_t flags)
{
    struct uartring_s *uring = mcast_out(dev, struct uartring_s, dev);

    while (!ring_empty(&uring->txring))
        DPRINT(ring_avail(&uring->txring));
    int ret = 0;

    if (sem_wait(&uring->rxsem))
        goto __exit1__;

    system_lock();
    while (ring_empty(&uring->rxring))
    {
        if (flags & IO_NOBLOCK)
            goto __exit0__;

        if (flags & IO_VIRTUAL_DISPLACE)
        {
            waitqueue_no_displace_wait(&uring->rxwait);
            goto __exit0__;
        }

        if (waitqueue_wait(&uring->rxwait))
            goto __exit0__;
    }

    if (size != 0)
        ret = ring_read(&uring->rxring, uring->rxbuffer, (char *)data, size);

__exit0__:
    system_unlock();
    sem_post(&uring->rxsem);

__exit1__:
    return ret;
}

static int uartring_room(struct char_device_s *dev)
{
    struct uartring_s *uring = mcast_out(dev, struct uartring_s, dev);
    return ring_room(&uring->txring);
}

static int uartring_avail(struct char_device_s *dev)
{
    struct uartring_s *uring = mcast_out(dev, struct uartring_s, dev);
    system_lock();
    int avail = ring_avail(&uring->rxring);
    system_unlock();
    return avail;
}

static void uartring_irq_handler(void *priv, int code)
{
    struct uartring_s *uring = (struct uartring_s *)priv;

    switch (code)
    {
    case UART_IRQCODE_TX:
    {
        if (ring_empty(&uring->txring))
        {
            uart_ctrirqs(uring->udev, UART_CTRIRQS_TXOFF);
            waitqueue_unwait_one(&uring->txwait);
            return;
        }

        char c = ring_getc(&uring->txring, uring->txbuffer);
        uart_sendbyte(uring->udev, c);
        return;
    }

    case UART_IRQCODE_RX:
    {
        char c;

        c = uart_recvbyte(uring->udev);
        ring_putc(&uring->rxring, uring->rxbuffer, c);

        waitqueue_unwait_one(&uring->rxwait);
        return;
    }

    case UART_IRQCODE_TC: // fallthrow
        (void)code;

    default:
        return;
    }
}

void uartring_install(struct uartring_s *uring, struct uart_s *uart)
{
    if (uart)
        uring->udev = uart;

    uring->udev->handler = uartring_irq_handler;
    uring->udev->handarg = (void *)uring;

    uart_enable(uring->udev, 1);
    uart_ctrirqs(uring->udev, UART_CTRIRQS_RXON);
}

const struct char_device_operation_s uartring_operations = {
    .write = uartring_write,
    .read = uartring_read,
    .avail = uartring_avail,
    .room = uartring_room,
};